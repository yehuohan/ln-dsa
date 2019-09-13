#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np

class Interpolation:
    """插值算法"""
    POLY = 'poly'
    LINEAR = 'linear'
    SPLINE = 'spline'
    def __init__(self, px: np.ndarray, py: np.ndarray, typ):
        """初始化
        :Parameters:
            - px: 插值节点x值
            - py: 插值节点y值
            - typ: 插值类型，支持poly, linear, spline
        """
        self.px = px
        self.py = py
        if typ == self.POLY:
            self.ipfunc = _PolynomialInterpolation(px, py)
        elif typ == self.LINEAR:
            self.ipfunc = _LinearInterpolation(px, py)
        elif typ == self.SPLINE:
            self.ipfunc = _SplineInterpolation(px, py)

    def __call__(self, x: float):
        """函数调用重载"""
        return self.ipfunc(x)

class _PolynomialInterpolation:
    """多项式插值
    使用Lagrange形式：
        fn(x) = sum(yi * li(x)), i = 0,1,2...,n
        li(x) = mul(x-xn) / mul(xi-xn), n = 0,1,2...i-1,i+1,...n
    """
    def __init__(self, px: np.ndarray, py: np.ndarray):
        """初始化
        :Parameters:
            - px: 插值节点x值
            - py: 插值节点y值
        """
        self.px = px
        self.py = py
        self.dpx = self.px.copy()
        self.dpxi = self.px.copy()

    def __call__(self, x: float):
        """函数调用重载
        :Parameters:
            - x: 待求插值点
        :Returns:
            待求插值点的函数值
        """
        self.dpx = x - self.px
        re = 0.0
        for i, v in enumerate(self.py):
            re += (v * self.__li(i))
        return re

    def __li(self, i: int):
        """插值基函数
        :Parameters:
            - i: 插值节点序列下标
        :Returns:
            基函数值
        """
        li_up = 1.0
        li_dn = 1.0
        self.dpxi = self.px[i] - self.px
        for k, _ in enumerate(self.px):
            if k != i:
                li_up *= self.dpx[k]
                li_dn *= self.dpxi[k]
        return li_up/li_dn

class _LinearInterpolation:
    """线性插值
        fn(x) = sum(yi * li(x)), i = 0,1,2...n
    """
    def __init__(self, px: np.ndarray, py: np.ndarray):
        """初始化
        :Parameters:
            - px: 插值节点x值
            - py: 插值节点y值
        """
        self.px = px
        self.py = py

    def __call__(self, x: float):
        """函数调用重载
        :Parameters:
            - x: 待求插值点
        :Returns:
            待求插值点的函数值
        """
        re = 0.0
        for k, v in enumerate(self.py):
            re += v * self.__li(x, k)
        return re

    def __li(self, x: float, i: int):
        """插值基函数
        :Parameters:
            - x: 待求插值点
            - i: 插值节点序列下标
        :Returns:
            基函数的值
        """
        n = len(self.px) - 1
        if i == 0:
            if (self.px[0] <= x) and (x <= self.px[1]):
                return (x - self.px[1]) / (self.px[0] - self.px[1])
            else:
                return 0
        elif 0 < i and i < n:
            if (self.px[i-1] <= x) and (x <= self.px[i]):
                return (x - self.px[i-1]) / (self.px[i] - self.px[i-1])
            elif (self.px[i] < x) and (x <= self.px[i+1]):
                return (x - self.px[i+1]) / (self.px[i] - self.px[i+1])
            else:
                return 0
        elif i == n:
            if (self.px[i-1] < x) and (x <= self.px[n]):
                return (x - self.px[n - 1]) / (self.px[n] - self.px[n - 1])
            else:
                return 0

class _SplineInterpolation:
    """三次样条插值(有问题)"""
    def __init__(self, px: np.ndarray, py: np.ndarray):
        """初始化
        :Parameters:
            - px: 插值节点x值
            - py: 插值节点y值
        """
        self.px = px
        self.py = py

        size = len(self.px)
        n = size - 1
        self.hi = np.array([0 for x in range(size)], dtype=np.float)
        self.alpha = self.hi.copy()
        self.beta = self.hi.copy()
        self.A = self.hi.copy()
        self.B = self.hi.copy()
        self.m = self.hi.copy()

        for k in range(0, size - 1):
            self.hi[k] = self.px[k + 1] - self.px[k]
        self.hi[n] = self.hi[0]

        ddsx0 = 0
        ddsxn = 0
        self.alpha[0] = 1
        self.alpha[n] = 0
        self.beta[0] = 3 / self.hi[0] * (self.py[1] - self.py[0]) - ddsx0 * self.hi[0] / 2
        self.beta[n] = 3 / self.hi[n-1] * (self.py[n] - self.py[n-1]) - ddsxn * self.hi[n-1] / 2
        for k in range(1, size - 1):
            self.alpha[k] = self.hi[k-1] / (self.hi[k-1] + self.hi[k])
            self.beta[k] = 3 * (((1 - self.alpha[k]) / self.hi[k-1]) * (self.py[k] - self.py[k-1])
                              + (self.alpha[k] / self.hi[k]) * (self.py[k+1] - self.py[k]))

        self.A[0] = -self.alpha[0] / 2
        self.B[0] = self.beta[0] / 2
        for k in range(1, size - 1):
            self.A[k] = -self.alpha[k] / (2 + (1 - self.alpha[k]) * self.A[k-1])
            self.B[k] = (self.beta[k] - (1 - self.alpha[k]) * self.B[k-1]) / (2 + (1 - self.alpha[k]) * self.A[k-1])
        self.B[n] = (self.beta[n] - (1 - self.alpha[n]) * self.B[n-1]) / (2 + (1 - self.alpha[n]) * self.A[n-1])

        self.m[n] = self.B[n]
        self.m[0] = self.m[n]
        for k in range(1, size - 1):
            self.m[k] = (self.m[k - 1] - self.B[k - 1]) / self.A[k - 1]

    def __call__(self, x: float):
        """函数调用重载
        :Parameters:
            - x: 待求插值点
        :Returns:
            待求插值点的函数值
        """
        k = 0
        while x > self.px[k + 1]:
            k += 1

        sa = (x - self.px[k+1]) / (self.px[k] - self.px[k+1])
        sb = (x - self.px[k]) / (self.px[k+1] - self.px[k])
        s1 = (1 + 2 * sb) * sa * sa * self.py[k]
        s2 = (1 + 2 * sa) * sb * sb * self.py[k+1]
        s3 = (x - self.px[k]) * sa * sa * self.m[k]
        s4 = (x - self.px[k+1]) * sb * sb * self.m[k+1]
        return (s1 + s2 + s3 + s4)
