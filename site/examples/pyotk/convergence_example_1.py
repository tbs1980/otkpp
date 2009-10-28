
from pyotk.native import *
from pyotk.testproblems import *
from pyotk.convergence import *

S = [ LinminBFGS(BFGSLmType.morethuente),
      LinminBFGS(BFGSLmType.fletcher),
      ConjGradMT(ConjGradType.FR),
      ConjGradMT(ConjGradType.PR) ]

P = [ Beale(),
      HelicalValley(),
      Wood(),
      ExtendedRosenbrock(n=10) ]

compare_convergence(S, P);
