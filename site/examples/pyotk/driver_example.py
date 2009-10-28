
from pyotk.native import *
from pyotk.testproblems import *

s = GSLfdfsolver('vector_bfgs2')
f = ExtendedRosenbrock(n=2)

x0 = (-1.2, 1)
sc = GradNormTest(eps=1e-8)

results = minimize(s, DefaultSolverSetup(), f.otk_instance,
                   sc, x0, NoConstraints(), 2, False)
