#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from scipy import misc

def on_key(event:mpl.backend_bases.KeyEvent):
    if event.key == 'escape':
        plt.close()


def read_image(filename):
    """Read image"""
    return misc.imread(filename)

def show_image(img:np.ndarray, img_svd:np.ndarray):
    """Show image"""
    fig = plt.figure('image-svd')
    fig.canvas.mpl_connect('key_press_event', on_key)
    ax1 = fig.add_subplot(121, xticks=[], yticks=[]);
    ax2 = fig.add_subplot(122, xticks=[], yticks=[]);
    ax1.imshow(img)
    ax2.imshow(img_svd)
    plt.show()

def calc_image_svd(img:list):
    """Calculate svd of image
    Return u,s,vh
    """
    img_r = img.swapaxes(1, 2).swapaxes(0, 1)
    svd_u, svd_s, svd_vh = np.linalg.svd(img_r, full_matrices=True)
    return [svd_u, svd_s, svd_vh]

def compree_svd(svd_u, svd_s, svd_vh):
    """Compress image
    Only reserve bigger singular value(奇异值), and remove the smaller
    singular value.
    """
    # What will happen when set m=p or n=p? Have a try.
    p = 150
    _,m,_ = svd_u.shape
    _,n,_ = svd_vh.shape
    u = np.zeros((3, m, p), np.float64)
    s = np.zeros((3, p), np.float64)
    vh = np.zeros((3, p, n), np.float64)

    # Only reserver the biggest p singular values
    u[:, 0:m, 0:p] = svd_u[:, 0:m, 0:p]
    s[:, 0:p] = svd_s[:, 0:p]
    vh[:, 0:p, 0:n] = svd_vh[:, 0:p, 0:n]

    print("Compression ratio:", float(m*n / (m*p + p + n*p)))
    return [u, s, vh]

def decompress_svd(size:tuple, svd_u, svd_s, svd_vh):
    """Decompress image
    Replace removed singular value with zero.
    """
    m, n = size[0:2]
    u = np.zeros((3, m, m), dtype=np.float64)
    s = np.zeros((3, min(m, n)), dtype=np.float64)
    vh = np.zeros((3, n, n), dtype=np.float64)

    _,p = svd_s.shape
    u[:, 0:m, 0:p] = svd_u[:, :, :]
    s[:, 0:p] = svd_s[:, :]
    vh[:, 0:p, 0:n] = svd_vh[:, :, :]

    # SVD equation: A = U * D * VH
    img_svd = np.zeros(size, dtype=np.uint8)
    for k in range(3):
        d = np.zeros((m, n), dtype=np.float64)
        d[:min(m, n), :min(m, n)] = np.diag(s[k, :])[:, :]
        img_svd[:,:,k] = np.dot(np.dot(u[k,:,:], d), vh[k,:,:])
    return img_svd


if __name__ == "__main__":
    img           = read_image('pic2.jpg')
    [u, s, vh]    = calc_image_svd(img)
    [cu, cs, cvh] = compree_svd(u, s, vh)
    # img_svd       = decompress_svd(img.shape, u, s, vh)
    img_svd       = decompress_svd(img.shape, cu, cs, cvh)
    show_image(img, img_svd)
