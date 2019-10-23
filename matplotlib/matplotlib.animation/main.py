import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

fig, ax = plt.subplots()
ax.grid()
ln, = plt.plot([])
xdata, ydata = [], []


def init():
    ax.set_xlim(0, 2 * np.pi)
    ax.set_ylim(-1, 1)
    ln.set_data(xdata, ydata)
    return ln,


def update(frame):
    xdata.append(frame)
    ydata.append(np.sin(frame))
    ln.set_data(xdata, ydata)
    return ln,


ani = FuncAnimation(
    fig,
    update,
    frames=np.linspace(0, 2 * np.pi, 128),
    init_func=init,
    blit=True,
    interval=10
)
plt.show()
