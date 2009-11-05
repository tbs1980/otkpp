from pyotk.native import *
from pyotk.plot2d import *
from pyotk.testproblems import *

f = PenaltyFunctionII(n=2)
x1 = -0.9
x2 = 0.75
y1 = -0.5
y2 = 1.5
z1 = f.plot_spec.z_range[0]
z2 = f.plot_spec.z_range[1]
z_logscale = f.plot_spec.z_logscale

s = GSLfsolver('nmsimplex')
x0 = (-0.8, 0.5)
results = minimize(s, DefaultSolverSetup(), f.otk_instance, MaxNumIterTest(100), x0, NoConstraints(), 0, False)
plot_iterates_on_contours(results, x1, x2, y1, y2, z1, z2)
