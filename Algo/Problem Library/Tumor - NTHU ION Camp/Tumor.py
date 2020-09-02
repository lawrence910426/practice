import random
from fibheap import *
import os

MAXN, MAXK, MAXT = 1000000, 10, 1   

N = random.randint(1, MAXN)
K = random.randint(1, MAXK)
T = [random.randint(0, MAXT) for i in range(N)]
alias =  str(MAXN) + " - " + str(MAXK) + " - " + str(MAXT)

with open("" + alias + " - 2.input", "w+") as f:
    f.write(str(N) + " " + str(K) + "\n")
    f.write(" ".join([str(item) for item in T]) + "\n")
