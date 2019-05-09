import matplotlib.pyplot as mpl
import numpy as np
from scipy import optimize

GROUPs = [
    "ABC", "ABD", "ABE", "ABF",
    "ACD", "ACE", "ACF", "ADE",
    "ADF", "AEF", "BCD", "BCE",
    "BCF", "BDE", "BDF", "BEF",
    "CDE", "CDF", "CEF", "DEF"
]

SUBJECTs = "ABCDEF"
Ns = [10, 9, 8, 7, 6, 5]
M = 20
m = 50
S = 7000
scale = [0.3, 0.25, 0.2, 0.125, 0.1, 0.025]
types = len(SUBJECTs)

def get_group_scales():
    coeff = np.zeros((6, 20))
    for subject_index, subject in enumerate(SUBJECTs):
        for i, item in enumerate(GROUPs):
            if subject in item:
                coeff[subject_index][i] = 1 - 3 * scale[subject_index]
            else:
                coeff[subject_index][i] = - 3 * scale[subject_index]
    ones = np.ones([1, 20])
    Aeq = np.r_[coeff, ones]
    beq = np.array([0, 0, 0, 0, 0, 0, 1])
    A = np.diag([-1 for _ in range(20)])
    b = np.zeros((20, 1))
    c = np.ones((20, ))
    # c = np.array([
    #     1, 2, 3, 4, 5,
    #     1, 2, 3, 4, 5,
    #     1, 2, 3, 4, 5,
    #     1, 2, 3, 4, 5,
    # ])
    res = optimize.linprog(c, A, b, Aeq, beq)
    print(res.x)
    print(res.fun)

get_group_scales()
