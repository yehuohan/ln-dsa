
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

# fx:  原函数
# dfx: 梯度
fx = lambda x: x[0] * x[0] + x[1] * x[1]
dfx = lambda x: 2 * x
# fx = lambda x: x[0] * x[0] - x[1] * x[1]
# dfx = lambda x: np.array([2, -2]) * x

grad = GradientDescent(dfx)
if not grad.go(startx=np.array([0.8, 0.8]), alpha=0.2, eps=0.001):
# if not grad.go(startx=np.array([-0.8, 0]), alpha=0.2, eps=0.001):
    print("Max iteration exceeded")

xx = np.linspace(-1, 1, 100, dtype=np.float)
xx, yy = np.meshgrid(xx, xx)
zz = fx(np.array([xx, yy]))
gxy = np.array(np.array(grad.xs_path))
gzz = np.array([0 for x in range(len(gxy))], dtype=np.float)
for k, v in enumerate(gxy):
    gzz[k] = fx(v)
size = len(gxy)

fig = plt.figure("grand")
fig.canvas.mpl_connect('key_press_event', on_key)
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(xx, yy, zz)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
line = []

def update(n):
    if n == 0:
        line.append(ax.plot(gxy[0:1, 0], gxy[0:1, 1], gzz[0], '*r', linewidth=1, markersize=5))
    else:
        line.append(ax.plot(gxy[n-1:n+1, 0], gxy[n-1:n+1, 1], gzz[n-1:n+1], '*-r', linewidth=1, markersize=5))
    return line

anim = animation.FuncAnimation(fig, func=update, frames=size, interval=300)
# anim.save('grad.gif', writer=animation.ImageMagickWriter(fps=5))
plt.show()
