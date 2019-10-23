import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation


fig, ax = plt.subplots()
ax.grid()
line, = ax.plot([])
xdata, ydata = [], []


def init():
    ax.set_ylim(-1.1, 1.1)
    ax.set_xlim(0, 10)
    line.set_data(xdata, ydata)
    return line,


def data_gen():
    cnt = 0
    t = 0
    while cnt < 1000:
        cnt += 1
        t += 0.1
        yield t, np.sin(2 * np.pi * t) * np.exp(-t / 10)


def run(data):
    t, y = data
    xmin, xmax = ax.get_xlim()
    if t >= xmax:
        ax.set_xlim(xmin, 2 * xmax)
        ax.figure.canvas.draw()
    xdata.append(t)
    ydata.append(y)
    line.set_data(xdata, ydata)
    return line,


ani = animation.FuncAnimation(
    fig,
    run,
    frames=data_gen,
    init_func=init,
    blit=False,
    repeat=False,
    interval=10
)
plt.show()
