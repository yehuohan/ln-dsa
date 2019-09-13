
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d as plt3d
import matplotlib.animation as animation
import moviepy.editor as mpy
from moviepy.video.io.bindings import mplfig_to_npimage
from grad import GradientDescent

mpl.rcParams['animation.convert_path'] = 'D:/ImageMagick/magick.exe'

def on_key(event):
    if event.key == 'escape':
        plt.close()

fx = lambda x : x * x
dfx = lambda x : 2 * x

grad = GradientDescent(dfx)
grad.go(startx=np.array([0.8]), alpha=0.2, eps=0.001)

xx = np.linspace(-1, 1, 100, dtype=np.float)
yy = fx(xx)
gxx = np.array(grad.xs_path)
gyy = fx(gxx)
size = len(gxx)

fig = plt.figure("grand")
fig.canvas.mpl_connect('key_press_event', on_key)
ax = fig.add_subplot(111)
ax.plot(xx, yy, '-b')
line = []

def update(n):
    if n == 0:
        line.extend(ax.plot(gxx[0], gyy[0], '*r', linewidth=1, markersize=5))
    else:
        line.extend(ax.plot(gxx[n-1:n+1], gyy[n-1:n+1], '*-r', linewidth=1, markersize=5))
    return line

anim = animation.FuncAnimation(fig, func=update, frames=size, interval=300)
anim.save('grad.gif', writer=animation.ImageMagickWriter(fps=5))
plt.show()
