
#include <otkpp/config.h>
#include <otkpp/function/Function.h>
#include <otkpp/localsolvers/native/LinminBFGS.h>
#include <otkpp/stopcrit/GradNormTest.h>

int main()
{
  Function f("(1-x)^2+100*(y-x*x)^2");
  LinminBFGS s(LinminBFGS::MORE_THUENTE);
  vector< double > x0(2);
  GradNormTest stopCrit(1e-8);
  NativeSolver::IterationStatus status;
  
  x0[0] = -1.2;
  x0[1] = 1.0;
  s.setup(f, x0);
  
  do {
    status = s.iterate();
  }
  while(status == NativeSolver::ITERATION_CONTINUE && 
        stopCrit.test(s) == false);
  
  printf("%-10s: niter: %-4d x*=%.5f  y*=%.5f  f(x*,y*)=%.5e\n", 
         s.getName().c_str(), s.getNumIter(), s.getX()[0], s.getX()[1], s.getFVal());
  
  return EXIT_SUCCESS;
}
