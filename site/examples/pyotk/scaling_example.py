from scaling import *

s = LinminBFGS(BFGSLmType.morethuente)
scaling_analysis(s)
s = ConjGradMT(ConjGradType.PR)
scaling_analysis(s)
