# This is a minimal example for invoking the driver routine 
# and plotting the results.

from pyotk.native import *
from pyotk.plot2d import *
from pyotk.testproblems import *

# Initialize the Beale test function and plotting ranges.
f = Beale()
x1 = f.plot_spec.x_range[0]
x2 = f.plot_spec.x_range[1]
y1 = f.plot_spec.y_range[0]
y2 = f.plot_spec.y_range[1]
z1 = f.plot_spec.z_range[0]
z2 = f.plot_spec.z_range[1]

# Initialize the line search BFGS algorithm with default parameters.
s = LinminBFGS()

# Call the driver routine and plot results.
#results = minimize(s, DefaultSolverSetup(), f.otk_instance, 
#                   f.stopcrit, f.x0, NoConstraints(), 0, False)
results = s.solve(f.f, f.x0, f.stopcrit, 
                  Solver.DefaultSetup(), NoConstraints(), False)

plot_iterates_on_contours(results, x1, x2, y1, y2, z1, z2)

