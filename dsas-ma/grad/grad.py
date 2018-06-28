#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np

class GradientDescent:
    """梯度下降法"""
    def __init__(self, gfx):
        """初始化参数
        :Parameters:
            - gfx: 目录标函数
        """
        self.gfx = gfx
        self.xs_path = []
        self.steps = 0

    def go(self, startx: np.ndarray, alpha: float, eps: float, maxit=10000):
        """梯度下降求解
        用xs_path记录下降路径，用self.steps记录下降次数
        :Parameters:
            - startx: 起始点
            - alpha: 下降速率
            - eps: 求解精度，即梯度为0的精度
            - maxit: 最大迭代次数
        :Returns:
            True: 成功下降到梯度零点
            False: 超出最大迭代次数
        """
        xs = startx
        self.steps = 0
        gfxs = self.gfx(xs)
        while True:
            self.steps += 1
            self.xs_path.append(xs)
            xs = xs - alpha * gfxs
            gfxs = self.gfx(xs)
            if np.linalg.norm(gfxs, 2) < eps:
                return True
            if self.steps >= maxit:
                return False
