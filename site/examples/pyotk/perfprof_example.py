
from pyotk.native import *
from pyotk.testproblems import *
from pyotk.perfprof import *

S = [ ConjGradMT(ConjGradType.FR),
      ConjGradMT(ConjGradType.PR),
      SteihaugSR1(),
      LinminBFGS(BFGSLmType.morethuente) ]

P = [ PowellBadlyScaled(),
      BrownBadlyScaled(),
      Beale(),
      HelicalValley(),
      Gaussian(),
      Box(m=5),
      Wood(),
      BrownDennis(m=20),
      BiggsEXP6(m=13),
      Watson(n=6),
      ExtendedRosenbrock(n=10),
      ExtendedPowellSingular(n=12),
      PenaltyFunctionI(n=10),
      PenaltyFunctionII(n=10),
      VariablyDimensioned(n=10),
      Trigonometric(n=5),
      ChebyQuad(n=8, m=8) ]

performance_profile(S, P, True)
