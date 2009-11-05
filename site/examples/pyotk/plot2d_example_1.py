from pyotk.native import *
from pyotk.plot2d import *
from pyotk.testproblems import *

f = Beale()
x1 = f.plot_spec.x_range[0]
x2 = f.plot_spec.x_range[1]
y1 = f.plot_spec.y_range[0]
y2 = f.plot_spec.y_range[1]
z1 = f.plot_spec.z_range[0]
z2 = f.plot_spec.z_range[1]

s = LinminBFGS()
results = minimize(s, DefaultSolverSetup(), f.otk_instance, f.stopcrit, f.x0, NoConstraints(), 0, False)
plot_iterates_on_contours(results, x1, x2, y1, y2, z1, z2)
