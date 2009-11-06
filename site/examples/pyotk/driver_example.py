# This is a minimal example demonstrating usage of 
# the driver routine for minimization algorithms.

from pyotk.native import *
from pyotk.testproblems import *

# Initialize the line search BFGS algorithm with 
# default parameters.
s = LinminBFGS()

# Initialize the extended Rosenbrock function 
# with two variables.
f = ExtendedRosenbrock(n=2)

# Start the iteration from [-1.2, 1] and initialize 
# the stopping criterion that tests gradient norm 
# against threshold value 1e-8.
x0 = (-1.2, 1)
sc = GradNormTest(eps=1e-8)

# Call the driver routine with the following parameters:
# - algorithm
# - algorithm parameters, default in this case
# - the function instance of the test problem
# - stopping criterion
# - starting point
# - constraints, none since we are using an 
#   unconstrained algorithm
# - output level, 2 = full output with information 
#   each iterate
# - time test mode, false since we are not measuring 
#   the computation time
results = minimize(s, DefaultSolverSetup(), f.otk_instance,
                   sc, x0, NoConstraints(), 2, False)
