#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import adpy as ap

def sigmoid(x):
    return ap.divide(
            ap.Constant(1),
            ap.add(
                ap.Constant(1),
                ap.exp(ap.substract(ap.Constant(0), x)))
            )

def sigmoid_(x):
    return ap.Constant(1) / (ap.Constant(1) + ap.exp(-x))

x = ap.Variable('x', 1)
y = ap.Variable('y', 0)
b = ap.Variable('b', 2)

f = ap.pow(ap.substract(sigmoid(ap.multiply(x, b)), y), ap.Constant(2))
f_ = (sigmoid_(x*b) - y) ** ap.Constant(2)

print(f)
print(f_)
print(f.partial_gradient(x))
print(f_.partial_gradient(x))
