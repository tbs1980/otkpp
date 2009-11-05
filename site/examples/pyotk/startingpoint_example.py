
from pyotk.startingpoint import *

f = Function("(x^2+y-11)^2+(x+y^2-7)^2")
p_min = [ (3, 2),
          (-2.805118, 3.131312),
          (-3.779310, -3.283186),
          (3.584428, -1.848126) ]

s = LinminBFGS(BFGSLmType.morethuente)
starting_point_analysis(s, f, p_min, -5, 5, -5, 5, 150)
