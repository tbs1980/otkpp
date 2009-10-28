
from pyotk.native import *
from pyotk.testproblems import *
from pyotk.convergence import *

tf = ExtendedRosenbrock(8)
results = minimize(GSLfdfsolver('vector_bfgs2'),
                    DefaultSolverSetup(), tf.otk_instance,
                    GradNormTest(eps=1e-8), tf.x0,
                    NoConstraints(), 0, False)
quantities = ['gradnorm', 'funcval']

convergence_plot(results, quantities)
