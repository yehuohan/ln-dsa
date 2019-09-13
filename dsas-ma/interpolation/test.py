#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
import interpolation as ip
from scipy import interpolate

def on_key(event):
    if event.key == 'escape':
        plt.close()

# px = np.linspace(-2, 2, 11)
# py = 1.0 / (1.0 + 25.0 * (px**2))
px = np.array([0, 1, 2, 4, 5])
py = np.array([10, 3, -20, 40, 85])

polyip = ip.Interpolation(px, py, 'poly')
linearip = ip.Interpolation(px, py, 'linear')
splineip = ip.Interpolation(px, py, 'spline')
# fx = np.linspace(-2, 2, 100, dtype=np.float)
fx = np.linspace(0, 5, 100, dtype=np.float)
pfy = fx.copy()
lfy = fx.copy()
sfy = fx.copy()
for i, v in enumerate(fx):
    pfy[i] = polyip(v)
    lfy[i] = linearip(v)
    sfy[i] = splineip(v)

fig = plt.figure()
fig.canvas.mpl_connect('key_press_event', on_key)
plt.plot(px, py, "*g")
plt.plot(fx, pfy, "r")
plt.plot(fx, lfy, "b")
# plt.plot(fx, sfy, "m")
plt.show()
