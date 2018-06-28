
import sys
import os
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

"""
    样本数据：
        m个样本
        X: (m x 2)
        Y: (m x 1)
    线性回归模型：
        H(t) = X*t = [x1, x2] * [t1; t2]
        x1=1时，即变成一维回归模型 y=a+bx
    模型参数：
        t: [t1; t2]，维度(2 x 1)
    目标函数：
        用均方误差衡量预测值与实际值的误差
        J(t) = (1/2/m) * sum{[H(x) - Y(x)]^2}
             = (1/2/m) * (X*t-Y)^T * (X*t-Y)
    目标函数梯度：
        dJ(t) = (1/m) X^T * (X*t-Y)
"""

m = 20
x0 = np.ones((m, 1), dtype=np.float)
x1 = np.arange(1, m+1, dtype=np.float).reshape(m, 1)
X = np.hstack((x0, x1))
Y = np.array([3, 4, 5, 5, 2, 4, 7, 8, 11, 8, 12,
    11, 13, 13, 16, 17, 18, 17, 19, 21], dtype=np.float).reshape(m, 1)

def fx(t):
    diff = np.dot(X, t) - Y
    return (1./(2.*m)) * np.dot(np.transpose(diff), diff)

def dfx(t):
    diff = np.dot(X, t) - Y
    return (1./m) * np.dot(np.transpose(X), diff)

grad = GradientDescent(dfx)
if not grad.go(startx=np.array([-10, 2]).reshape(2, 1), alpha=0.01, eps=0.000001, maxit=10000):
    print("Max iteration exceeded")
else:
    print("Iteration steps:", grad.steps)

"""使用matplotlib生成gif动画"""
gxx = np.array([[1, 1], [1, 20]])
gtt = np.array(np.array(grad.xs_path))
size = len(gtt)
gyy = np.dot(gxx, gtt[0])
gyy_final = np.dot(gxx, gtt[size-1])

fig = plt.figure("grand")
fig.canvas.mpl_connect('key_press_event', on_key)
ax = fig.add_subplot(111)
ax.plot(x1, Y, 'og')
ax.plot(gxx[:,1], gyy_final, '*-b')
line = ax.plot(gxx[:,1], gyy, '-r')

def update(n):
    n = (n * 50) % size
    gyy = np.dot(gxx, gtt[n])
    line[0].set_ydata(gyy)
    return line

anim = animation.FuncAnimation(fig, func=update, frames=size, interval=300)
# anim.save('grad.gif', writer=animation.ImageMagickWriter(fps=5))
plt.show()

"""使用moviepy生成gif动画"""
if 0:
    dura = 4
    def make_frame(t):
        n = int(t * size / dura) % size
        gyy = np.dot(gxx, gtt[n])
        line[0].set_ydata(gyy)
        return mplfig_to_npimage(fig)

    gif = mpy.VideoClip(make_frame, duration=dura)
    gif.write_gif("grad.gif", fps=25)
