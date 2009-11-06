# This example demonstrates plotting different quantities 
# as a function of used iteration steps.

from pyotk.native import *
from pyotk.testproblems import *
from pyotk.convergence import *

# Initialize the extended Rosenbrock function with 8 variables.
tf = ExtendedRosenbrock(8)
# Start iteration from the default starting point 
# and use the BFGS algorithm with line searches.
results = minimize(LinminBFGS(),
                   DefaultSolverSetup(), tf.otk_instance,
                   GradNormTest(eps=1e-10), tf.x0,
                   NoConstraints(), 0, False)

# Choose gradient norm and function value and plot them.
quantities = ['gradnorm', 'funcval']
convergence_plot(results, quantities)
