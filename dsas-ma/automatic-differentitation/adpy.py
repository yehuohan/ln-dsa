#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Automatic Differentitation：自动求导
基本原理是微分的链式法则。
"""

class DType():
    """常量和变量的数据类型"""
    DTYPE_INT8   = 'int8'
    DTYPE_INT16  = 'int16'
    DTYPE_INT32  = 'int32'
    DTYPE_INT64  = 'int64'
    DTYPE_UINT8  = 'uint8'
    DTYPE_UINT16 = 'uint16'
    DTYPE_UINT32 = 'uint32'
    DTYPE_UINT64 = 'uint64'
    DTYPE_FLOAT  = 'float32'
    DTYPE_DOUBLE = 'float64'
    DTYPE_STRING = 'string'
    DTYPE_BOOL   = 'bool'
    def __init__():
        pass

class Base():
    """自动求导基类"""
    G_TYPE_CONSTANT  = 'CONSTANT'
    G_TYPE_VARIABLE  = 'VARIABLE'
    G_TYPE_OPERATION = 'OPERATION'
    def __init__(self, name, value, type):
        self.name = name
        self.value = value
        self.type = type
        # self.dtype = dtype

    def __repr__(self):
        return self.expression()

    def __add__(self, op):
        return add(self, op)

    def __sub__(self, op):
        return substract(self, op)

    def __neg__(self):
        return substract(Constant(0), self)

    def __mul__(self, op):
        return multiply(self, op)

    def __truediv__(self, op):
        return divide(self, op)

    def __pow__(self, op):
        return pow(self, op)

    def partial_gradient(self, partial):
        """求偏导"""
        pass

    def expression(self):
        """表达式"""
        pass

class Constant(Base):
    """常量Constant"""
    G_STATIC_VARIABLE = {}
    def __init__(self, value):
        try:
            self.G_STATIC_VARIABLE['counter'] += 1
        except:
            self.G_STATIC_VARIABLE.setdefault('counter', 0)
        self.value = value
        self.name = 'CONSTANT_' + str(self.G_STATIC_VARIABLE['counter'])
        self.type = self.G_TYPE_CONSTANT

    def partial_gradient(self, partial:Base):
        """常量求导为0"""
        return Constant(0)

    def expression(self):
        return str(self.value)

class Variable(Base):
    """变量Vairable"""
    def __init__(self, name, value=None):
        self.name = name
        self.value = value
        self.type = self.G_TYPE_VARIABLE

    def partial_gradient(self, partial:Base):
        """对基本变量求导"""
        if partial.name == self.name:
            return Constant(1)
        return Constant(0)

    def expression(self):
        return str(self.name)

class OpType():
    """操作符类型"""
    OP_ADD       = 'add'
    OP_SUBSTRACT = 'minus'
    OP_MULTIPLY  = 'multiply'
    OP_DIVIDE    = 'division'
    OP_POW       = 'pow'
    OP_EXP       = 'exp'
    OP_LN        = 'ln'
    def __init__(self):
        pass

class Operation(Base):
    """操作符Operation"""
    def __init__(self, opl:Base, opr:Base, optype):
        """操作符初始化
        :Parameters:
            - opl: 左操作数
            - opr: 右操作数
            - optype: 运算符类型
        """
        self.opl = opl
        self.opr = opr
        self.optype = optype
        self.type = Base.G_TYPE_OPERATION

    def partial_gradient(self, partial:Base):
        """操作符求导运算
        通过递归实现链式求导
        :Parameters:
            - partial: 对partial求导
        :Returns:
        :Raises:
        """
        if partial.type != self.G_TYPE_VARIABLE:
            return None
        if self.optype == OpType.OP_ADD or self.optype == OpType.OP_SUBSTRACT:
            # y=u+v, y'=u'+v'
            return operation_wrapper(
                    self.opl.partial_gradient(partial),
                    self.opr.partial_gradient(partial),
                    self.optype)
        elif self.optype == OpType.OP_MULTIPLY:
            # y=uv, y'=u'v+uv'
            return operation_wrapper(
                    operation_wrapper(self.opl.partial_gradient(partial), self.opr, OpType.OP_MULTIPLY),
                    operation_wrapper(self.opl, self.opr.partial_gradient(partial), OpType.OP_MULTIPLY),
                    OpType.OP_ADD)
        elif self.optype == OpType.OP_DIVIDE:
            # y=u/v, y'= (u'v-uv')/(v*v)
            return operation_wrapper(
                    operation_wrapper(
                        operation_wrapper(self.opl.partial_gradient(partial), self.opr, OpType.OP_MULTIPLY),
                        operation_wrapper(self.opl, self.opr.partial_gradient(partial), OpType.OP_MULTIPLY),
                        OpType.OP_SUBSTRACT),
                    operation_wrapper(self.opr, Constant(2), OpType.OP_POW),
                    OpType.OP_DIVIDE)
        elif self.optype == OpType.OP_POW:
            # y=u^n, y'=nu^(n-1)*u'
            return operation_wrapper(
                    operation_wrapper(
                        self.opr,
                        operation_wrapper(self.opl, Constant(self.opr.value-1), OpType.OP_POW),
                        OpType.OP_MULTIPLY),
                    self.opl.partial_gradient(partial),
                    OpType.OP_MULTIPLY)
        elif self.optype == OpType.OP_EXP:
            # y=e^u, y'=e^u*u'，只有一个操作数，故u在左边(opl)
            return operation_wrapper(self, self.opl.partial_gradient(partial), OpType.OP_MULTIPLY)
        elif self.optype == OpType.OP_LN:
            # y=ln(u), y'=1/u*u'
            return operation_wrapper(
                    operation_wrapper(Constant(1), self.opl, OpType.OP_DIVIDE),
                    self.opl.partial_gradient(partial),
                    OpType.OP_MULTIPLY)

    def expression(self):
        if self.optype == OpType.OP_ADD:
            if self.opr.type == Base.G_TYPE_CONSTANT and self.opr.value == 0:
                return self.opl.expression()
            elif self.opl.type == Base.G_TYPE_CONSTANT and self.opl.value == 0:
                return self.opr.expression()
            else:
                return '(' + self.opl.expression() + '+' + self.opr.expression() + ')'
        elif self.optype == OpType.OP_SUBSTRACT:
            if self.opr.type == Base.G_TYPE_CONSTANT and self.opr.value == 0:
                return self.opl.expression()
            elif self.opl.type == Base.G_TYPE_CONSTANT and self.opl.value == 0:
                return '(-' + self.opr.expression() + ')'
            else:
                return '(' + self.opl.expression() + '-' + self.opr.expression() + ')'
        elif self.optype == OpType.OP_MULTIPLY:
            if self.opr.type == Base.G_TYPE_CONSTANT and self.opr.value == 1:
                return self.opl.expression()
            elif self.opl.type == Base.G_TYPE_CONSTANT and self.opl.value == 1:
                return self.opr.expression()
            else:
                return self.opl.expression() + '*' + self.opr.expression()
        elif self.optype == OpType.OP_DIVIDE:
            if self.opr.type == Base.G_TYPE_CONSTANT and self.opr.value == 1:
                return self.opl.expression()
            else:
                return self.opl.expression() + '/' + self.opr.expression()
        elif self.optype == OpType.OP_POW:
            if self.opr.type == Base.G_TYPE_CONSTANT and self.opr.value == 1:
                return self.opl.expression()
            else:
                return self.opl.expression() + '^' + self.opr.expression()
        elif self.optype == OpType.OP_EXP:
            if self.opl.type == Base.G_TYPE_CONSTANT and self.opl.value == 1:
                return 'e'
            else:
                return 'e^' + self.opl.expression()
        elif self.optype == OpType.OP_LN:
            return 'ln(' + self.opl.expression() + ")"


def operation_wrapper(opl:Base, opr:Base, optype):
    """Operation外层封装函数"""
    if opr != None:
        if optype == OpType.OP_ADD:
            if opl.type == Base.G_TYPE_CONSTANT and opl.value == 0:
                return opr
            if opr.type == Base.G_TYPE_CONSTANT and opr.value == 0:
                return opl
        elif optype == OpType.OP_SUBSTRACT:
            if opr.type == Base.G_TYPE_CONSTANT and opr.value == 0:
                return opl
        elif optype == OpType.OP_MULTIPLY:
            if opl.type == Base.G_TYPE_CONSTANT and opr.type == Base.G_TYPE_CONSTANT:
                return Constant(opl.value * opr.value)
            if opl.type == Base.G_TYPE_CONSTANT and opl.value == 1:
                return opr
            if opl.type == Base.G_TYPE_CONSTANT and opl.value == 0:
                return Constant(0)
            if opr.type == Base.G_TYPE_CONSTANT and opr.value == 1:
                return opl
            if opr.type == Base.G_TYPE_CONSTANT and opr.value == 0:
                return Constant(0)

    return Operation(opl, opr, optype)

def add(opl:Base, opr:Base):
    """加法"""
    return operation_wrapper(opl, opr, OpType.OP_ADD)

def substract(opl:Base, opr:Base):
    """减法"""
    return operation_wrapper(opl, opr, OpType.OP_SUBSTRACT)

def multiply(opl:Base, opr:Base):
    """乘法"""
    return operation_wrapper(opl, opr, OpType.OP_MULTIPLY)

def divide(opl:Base, opr:Base):
    """除法"""
    return operation_wrapper(opl, opr, OpType.OP_DIVIDE)

def pow(opl:Base, opr:Base):
    """幂"""
    return operation_wrapper(opl, opr, OpType.OP_POW)

def exp(opl:Base):
    """指数"""
    return operation_wrapper(opl, None, OpType.OP_EXP)

def ln(opl:Base):
    """ln函数"""
    return operation_wrapper(opl, None, OpType.OP_LN)

