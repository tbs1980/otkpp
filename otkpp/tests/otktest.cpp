
#include "ConjGradMT.h"
#include "DoglegBFGS.h"
#include "Function.h"
#ifdef WITH_GSL
#include "GSLFSolver.h"
#include "GSLFDFSolver.h"
#endif
#include "HookeJeeves.h"
#include "MGHTestFunction.h"
#include "MNewton.h"
#include "NativeSolver.h"
#include "LinminBFGS.h"
#include "SteihaugSR1.h"
#include "PARTAN.h"
#include "XDistToMinTest.h"
#ifdef WITH_FORTRAN
#include "LBFGSB.h"
#include "LMBM.h"
#endif

#include <cstdlib>
#include <iostream>
#include <list>
#include <string>

static const std::string F_EXPR = "(1-x)^2+100*(y-x*x)^2";
//static const std::string F_EXPR = "(1.5-x*(1-y))^2+(2.25-x*(1-y^2))^2+(2.625-x*(1-y^3))^2";
//static const std::string F_EXPR = "x*x+y*y";
static const unsigned int MAX_NUM_ITER = 10000;

static void initAlgorithmList(std::list< NativeSolver * > &algoList)
{
#ifdef WITH_GSL
  algoList.push_back(new GSLFSolver(gsl_multimin_fminimizer_nmsimplex));
  algoList.push_back(new GSLFDFSolver(gsl_multimin_fdfminimizer_conjugate_fr));
  algoList.push_back(new GSLFDFSolver(gsl_multimin_fdfminimizer_conjugate_pr));
  algoList.push_back(new GSLFDFSolver(gsl_multimin_fdfminimizer_vector_bfgs));
  algoList.push_back(new GSLFDFSolver(gsl_multimin_fdfminimizer_vector_bfgs2));
#endif
  algoList.push_back(new DoglegBFGS());
  algoList.push_back(new SteihaugSR1());
  algoList.push_back(new LinminBFGS(LinminBFGS::FLETCHER));
  algoList.push_back(new LinminBFGS(LinminBFGS::MORE_THUENTE));
  algoList.push_back(new LinminBFGS(LinminBFGS::MORE_THUENTE, 8));
  algoList.push_back(new MNewton());
  algoList.push_back(new PARTAN());
  algoList.push_back(new HookeJeeves());
  algoList.push_back(new ConjGradMT(ConjGradMT::FLETCHER_REEVES));
  algoList.push_back(new ConjGradMT(ConjGradMT::POLAK_RIBIERE));
#ifdef WITH_FORTRAN
  algoList.push_back(new LBFGSB());
#endif
  //algoList.push_back(new LMBMSolver());
}

void initFuncList(std::list< Function * > &funcList)
{
  funcList.push_back(new Function(F_EXPR, Function::DERIV_SYMBOLIC));
  funcList.push_back(new ExtendedRosenbrock(2, Function::DERIV_FDIFF_CENTRAL_2));
}

static void freeAlgorithmList(std::list< NativeSolver * > &algoList)
{
  std::list< NativeSolver * >::iterator it;
  for(it = algoList.begin(); it != algoList.end(); it++)
    delete *it;
}

static void freeFuncList(std::list< Function * > &funcList)
{
  std::list< Function * >::iterator it;
  for(it = funcList.begin(); it != funcList.end(); it++)
    delete *it;
}

static void printResults(const std::string &algoName,
                         int n_iter,
                         const vector< double > &x,
                         double f,
                         NativeSolver::IterationStatus status)
{
  if(status == NativeSolver::ITERATION_CONTINUE || 
     status == NativeSolver::ITERATION_SUCCESS)
    printf("%-15s: niter: %-4d x*=%.5f  y*=%.5f  f(x*,y*)=%.5e\n",
           algoName.c_str(),
           n_iter, x[0], x[1], f);
  else
    printf("%-15s: FAILURE (%s)\n", algoName.c_str(), "???"); // TODO: error code string
}

#ifdef WITH_FORTRAN
static void testLBFGSB()
{
  LBFGSB solver;
  
  Function f(F_EXPR);
  vector< double > x0(2);
  x0[0] = -1.2;
  x0[1] = 1.0;
  
  solver.setup(f, x0);
  for(int i = 0; i < 100; i++)
    solver.iterate();
}

static void testLMBM()
{
  LMBM solver;
  
  Function f(F_EXPR);
  vector< double > x0(2);
  x0[0] = -1.2;
  x0[1] = 1.0;
  
  solver.solve(f, x0);
}
#endif

#include "CompoundStoppingCriterion.h"
#include "GradNormTest.h"
#include "FDistToMinTest.h"

int main(int argc, char **argv)
{
  GradNormTest t1(1e-8);
  FDistToMinTest t2(0, 1e-8, false);
  CompoundStoppingCriterion t3 = CompoundStoppingCriterion(t1) + t2;
  
  std::list< NativeSolver * > algoList;
  std::list< Function * > funcList;
  vector< double > x0(2);
  std::list< Function * >::const_iterator f;
  std::list< NativeSolver * >::const_iterator s;
  NativeSolver::IterationStatus status;
  StoppingCriterion *stopCrit;
  int k;
  
  initAlgorithmList(algoList);
  initFuncList(funcList);
  vector< double > xMin(2);
  xMin[0] = 1.0;
  xMin[1] = 1.0;
  stopCrit = new XDistToMinTest(xMin, 1e-6, false);
  
  x0[0] = -1.2;
  x0[1] = 1.0;
  
  int fi = 0;
  for(f = funcList.begin(); f != funcList.end(); f++)
  {
    if(fi == 0)
      std::cout<<"Rosenbrock function with symbolic evaluation:"<<std::endl;
    else
      std::cout<<"Precompiled Rosenbrock function with finite-difference derivatives:"<<std::endl;
    
    for(s = algoList.begin(); s != algoList.end(); s++)
    {
      (*s)->setup(**f, x0);
      
      k = 0;
      status = NativeSolver::ITERATION_CONTINUE;
      do
      {
        status = (*s)->iterate();
        k++;
      }
      while(status == NativeSolver::ITERATION_CONTINUE && 
            k < MAX_NUM_ITER && 
            ((*s)->hasBuiltInStoppingCriterion() || stopCrit->test(**s) == false));
      
      printResults((*s)->getName(), k, (*s)->getX(), 
                  (*s)->getFVal(), status);
    }
    
    fi++;
  }
  
  freeAlgorithmList(algoList);
  freeFuncList(funcList);
  delete stopCrit;
  
  return EXIT_SUCCESS;
}