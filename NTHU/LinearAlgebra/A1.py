#!/usr/bin/env python
# coding: utf-8

# In[25]:


import numpy as np

def EnumerateAll(mlist, m, n):
    ''' Enumerate all the n-tuple from mlist.
        where mlist contains m numbers.
        We assume m >= n.
    ''' 

    # this is just for demo purpose.
    # write your own code for question (3) here.
    def recursion(last, dep):
        if dep == n - 1:
            return [[i] for i in mlist[0:last]]
        ans = []
        for l in range(0, last):
            rec = recursion(l, dep + 1)
            for item in rec:
                temp = item[:]
                temp.append(mlist[l])
                ans.append(temp)
        return ans
                        
    return recursion(m, 0)
    return [[0,1], [0,2], [1,2]]
    

def SolveLP(A, b, G):
    '''Solve the linear programming problem
        Max G(x)
        st. Ax <= b
             x >= 0
    '''
    # step 0: initialization
    maxg = 0;
    
    # step 1a: enumuate all combinations
    [m, n] = A.shape
    lst = EnumerateAll(np.arange(m), m, n)

    # step 1b: compute all the intersection points
    points = [];
    for idx in lst:
        Ai = A[idx, :]
        bi = b[idx]
        try:
            xi = np.linalg.solve(Ai, bi)
        except:
            continue
        
        # step 2: check the feasibility of the itersection point
        feasible = 1
        for i in range(m):
            if np.dot(A[i,:], xi) > b[i]:  # violate a constraints
                feasible = 0
        if feasible == 1:            # only add the feasible point
            points.append(xi)
        
    # step 3: evaluate the G function for all intersection points
    values = []
    for ptx in points:
        values.append(np.dot(G[0:n], ptx)+G[-1])
    
    # step 4: find the point with the largest value as the result
    maxg = max(values)
    maxidx = values.index(maxg)
    x = points[maxidx]
    
    return x, maxg
    
#-------------------------------#
# main program starts from here.#
#-------------------------------#
# Put all the coefficients of the constrains into a matrix A and a vector b

A = np.array([
    [1,     0,      0,      0],
    [-1,    0,      0,      0],
    [0,     1,      0,      0],
    [0,     -1,     0,      0],
    [0,     0,      1,      0],
    [0,     0,      -1,     0],
    [0,     0,      0,      1],
    [0,     0,      0,      -1],
    [0,     5,      10,     3]
])
b = np.array([
    1000, 
    -300, 
    5,
    -1,
    3,
    -1,
    1000,
    -50,
    2000
])
G = np.array([
    np.log(1 + 0.001), 
    np.log(1 + 0.01), 
    np.log(1 + 0.03),
    np.log(1 + 0.015)
])

# solve this problem
[x, maxg] = SolveLP(A, b, G)
print(x)
print(maxg)

