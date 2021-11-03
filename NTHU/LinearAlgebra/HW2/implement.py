import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.axes3d import Axes3D
import numpy as np
import math
from matplotlib.animation import FuncAnimation, PillowWriter 



def set_object(R, T):
    # drawing
    for oo, mat in zip(objs, data):
        n = len(mat[0])
        # rotation 
        mat = np.dot(R, mat) + np.dot(T, np.ones((1,n)))
        # set the object    
        oo.set_data(mat[0], mat[1])
        oo.set_3d_properties(mat[2])
    return objs

def roll(i):
    phi = 2*i*math.pi/N
    # define the rotation matrix
    R = np.array([[1,             0,             0],
                  [0, math.cos(phi), -math.sin(phi)], 
                  [0, math.sin(phi), math.cos(phi)]]);
    
    m = len(data)
    T = np.zeros((m,1))     # no translation
    return set_object(R, T)

def yaw(i):
    phi = 2*i*math.pi/N
    # define the rotation matrix
    R = np.array([[math.cos(phi), -math.sin(phi), 0], 
                  [math.sin(phi),  math.cos(phi), 0], 
                  [0,              0,             1]]);
    
    m = len(data)
    T = np.zeros((m,1))     # no translation
    return set_object(R, T)

def pitch(i):
    phi = 2*i*math.pi/N
    # define the rotation matrix
    R = np.array([[ math.cos(phi), 0, -math.sin(phi)], 
                  [0,              1,             0],
                  [math.sin(phi), 0, math.cos(phi)]]);
    
    m = len(data)
    T = np.zeros((m,1))     # no translation
    ax.text(10, 10, 10, str(phi))
    return set_object(R, T)


def myMovie_basic(i):
    T = np.array([[xdata[i]], [ydata[i]], [zdata[i]]])
    R = np.eye(3)
    return set_object(R, T)


def myMovie(i):
    T = np.array([[xdata[i]], [ydata[i]], [zdata[i]]])
    # yaw
    # slip a circle into N equal angles
    phi = 0
    R = np.array([
      [math.cos(phi), -math.sin(phi), 0], 
      [math.sin(phi), math.cos(phi), 0], 
      [0,       0,       1]
    ])

    # add pitch
    theta = -2 * np.pi * i / len(xdata)
    R = np.dot(R, np.array([
      [math.cos(theta), 0, -math.sin(theta)], 
      [0,              1,             0],
      [math.sin(theta), 0, math.cos(theta)]
    ]))
    
    # add roll
    R = np.dot(R, np.array([
      [1,              0,             0],
      [0, math.cos(-0), -math.sin(-0)], 
      [0, math.sin(-0),  math.cos(-0)]
    ]))
    return set_object(R, T)


# -------------- main program starts here ----------------#
N = 100
fig = plt.gcf()
ax = Axes3D(fig, xlim=(-15, 15), ylim=(-15, 15), zlim=(-15, 15))


# data matrix
edges = 10
M1 = np.array([
  [3 * np.sin(np.pi * (2 * i + 1) / edges) for i in range(0, edges + 1)],
  [3 * np.cos(np.pi * (2 * i + 1) / edges) for i in range(0, edges + 1)],
  [0                               for i in range(0, edges + 1)],
])
M2 = np.array([
  [4 * np.sin(np.pi * (2 * i + 1) / edges) for i in range(0, edges + 1)],
  [4 * np.cos(np.pi * (2 * i + 1) / edges) for i in range(0, edges + 1)],
  [0                               for i in range(0, edges + 1)],
])
M3 = np.array([
  [5 * np.sin(np.pi * (2 * i + 1) / edges) for i in range(0, edges + 1)],
  [5 * np.cos(np.pi * (2 * i + 1) / edges) for i in range(0, edges + 1)],
  [0                               for i in range(0, edges + 1)],
])
M4 = np.array([
  [-0.6704,   0,      0,        -0.8617,    0.9550], 
  [0.9859,    1.7782, -1.2133,  -1.2406,    -1.2406],
  [0,         0,      0,        0,          0]
])
data = [M1, M2, M3, M4]

# create 3D objects list
O1, = ax.plot3D(M1[0], M1[1], M1[2])
O2, = ax.plot3D(M2[0], M2[1], M2[2])
O3, = ax.plot3D(M3[0], M3[1], M3[2])
O4, = ax.plot3D(M4[0], M4[1], M4[2])
objs = [O1, O2, O3, O4]

# trajectory data
t = np.arange(0, 1, 0.01)
xdata = 20 * t - 10
ydata = 20 * t - 10
zdata = -75 * t * t + 75 * t - 10

# basic rotations
# ani = FuncAnimation(fig, roll, frames=N, interval=10)
# ani = FuncAnimation(fig, yaw, frames=N, interval=10)
# ani = FuncAnimation(fig, pitch, frames=N, interval=1000)
ani = FuncAnimation(fig, myMovie, frames=len(xdata), interval=100)

ani.save('/content/drive/My Drive/HW.gif', writer='imagemagick', fps=30)
# ani.save('/content/drive/My Drive/A2.gif', writer='imagemagick', fps
