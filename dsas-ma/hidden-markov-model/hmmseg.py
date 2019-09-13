#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
HMM实践。
 - HMMSeg: 中文分词
"""

import numpy as np

class HmmSeg:
    """
    模型参数：
    - n   隐含状态数(hidden states)
    - m   观测数(observable symbols)
    - A   隐含状态转移矩阵(transition probability matrix, n x n)
    - B   观测混合矩阵(observable symbols confusion matrix, n x m)
    - Pi  初始状态矩阵(initial state's probability matrix, n)
    """
    PARAM_A = "param_A.txt"
    PARAM_B = "param_B.txt"
    PARAM_Pi = "param_Pi.txt"
    STATE_B = 0     # 'B': Begin
    STATE_M = 1     # 'M': Member
    STATE_E = 2     # 'E': End
    STATE_S = 3     # 'S': Single
    STATE_I = 4     # 'I': Inited state
    STATE_P = 5     # 'P': Pass state
    STATE_MAP = ('B', 'M', 'E', 'S', 'I', 'P')
    PUNCTUATION = [ '。', '，', '！', '？', '；', '：', '、',
                    '‘', '’', '“', '”', '《', '》', '（', '）']
    TYPE_S = 1      # Space
    TYPE_L = 2      # change Line
    TYPE_P = 3      # Punctuation
    TYPE_C = 4      # Character

    def __init__(self):
        self.n = 4          # S = [self.STATE_B, self.STATE_M, self.STATE_E, self.STATE_S]
        self.m = 65536      # O = [charaters]
        self.S = ['B', 'M', 'E', 'S']
        self.A = None
        self.B = None
        self.Pi = None
        for k in range(len(self.PUNCTUATION)):
            self.PUNCTUATION[k] = ord(self.PUNCTUATION[k])

    def __save(self):
        try:
            np.savetxt(self.PARAM_A, self.A)
            np.savetxt(self.PARAM_B, self.B)
            np.savetxt(self.PARAM_Pi, self.Pi)
        except AttributeError:
            print("No param in HmmSeg.")
            return False
        return True

    def __load(self):
        try:
            self.A = np.loadtxt(self.PARAM_A)
            self.B = np.loadtxt(self.PARAM_B)
            self.Pi = np.loadtxt(self.PARAM_Pi)
        except OSError:
            print("No param file exist.")
            return False
        return True

    def __type_ch(self, ch):
        oh = ord(ch)
        assert(0 <= oh and oh <= self.m)
        if oh == ord(' '):
            return self.TYPE_S
        elif oh == ord('\n'):
            return self.TYPE_L
        elif oh in self.PUNCTUATION:
            return self.TYPE_P
        else:
            return self.TYPE_C

    def __mark_state(self, next_ch):
        """
        根据字符类型来标记State
        mark table:
                     | __ch  | next_ch
        oh0          | oh1   | oh2
        __state_last | state |
        """
        if not self.__ch:
            self.__ch = next_ch
            return

        oh1 = self.__type_ch(self.__ch)
        oh2 = self.__type_ch(next_ch)
        if oh1 == self.TYPE_S:
            state = self.STATE_P
        elif oh1 == self.TYPE_L:
            state = self.STATE_I
        elif oh1 == self.TYPE_P:
            state = self.STATE_S
        elif oh1 == self.TYPE_C:
            if oh2 == self.TYPE_S or oh2 == self.TYPE_L or oh2 == self.TYPE_P:
                state = self.STATE_E if (self.__state_last == self.STATE_M or self.__state_last == self.STATE_B) else self.STATE_S
            elif oh2 == self.TYPE_C:
                state = self.STATE_B if (self.__state_last == self.STATE_I or self.__state_last == self.STATE_P) else self.STATE_M

        self.c2s += "{}|{:>2}\n".format(self.__ch, self.STATE_MAP[state])

        self.__accuml_param(state, ord(self.__ch))
        self.__ch = next_ch
        self.__state_last = state

    def __accuml_param(self, state, oh):
        """
        累计频数
        """
        if state == self.STATE_I:
            self.__sl = state
        elif state == self.STATE_P:
            pass
        else:
            assert(self.__sl != self.STATE_P)
            if self.__sl == self.STATE_I:
                self.Pi[state] += 1
            else:
                self.A[self.__sl][state] += 1
            self.B[state][oh] += 1
            self.__sl = state

    def __calc_param(self):
        """
        通过频率计算概率
        """
        sum_col = np.sum(self.A, 1)
        for k in range(self.A.shape[0]):
            self.A[k] = self.A[k] / sum_col[k]
        self.B += 1     # 防止频率为0
        sum_col = np.sum(self.B, 1)
        for k in range(self.B.shape[0]):
            self.B[k] = self.B[k] / sum_col[k]
        self.Pi = self.Pi / self.Pi.sum()

    def train(self, train_data):
        """
        中文分词参数训练
        """
        self.A = np.zeros((self.n, self.n), dtype=np.float)
        self.B = np.zeros((self.n, self.m), dtype=np.float)
        self.Pi = np.zeros(self.n, dtype=np.float)

        with open(train_data, 'r') as fp:
            self.__ch = ''                      # current character
            self.__state_last = self.STATE_I    # last state in __mark_state
            self.__sl = self.STATE_I            # last state in __accuml_param
            self.c2s = ''                       # character to state string
            while True:
                ch = fp.read(1)
                if not ch:
                    break;
                self.__mark_state(ch)
        self.__calc_param()

        if self.c2s:
            with open("c2s.txt", 'w') as fp:
                fp.write(self.c2s)

        if not self.__save():
            return False
        return True

    def __forward(self, seq):
        """
        前向算法，用于计算给定序列的概率。
        :Parameters:
            - seq: 观测序列
        :Returns:
            - 返回最大概率
        """
        ot = ord(seq[0])
        assert(0 <= ot and ot <= self.m)
        alpha = np.zeros(self.A.shape[0], dtype=np.float)
        p = np.zeros(self.A.shape[0], dtype=np.float)

        # p_i(t): 序列为x1~xt且状态zt=i时的概率
        for i in range(self.A.shape[0]):
            alpha[i] = self.Pi[i] * self.B[i][ot]
        p = np.copy(alpha)

        for t in range(1, len(seq)):
            ot = ord(seq[t])
            assert(0 <= ot and ot <= self.m)
            for i in range(self.A.shape[0]):
                alpha[i] = 0.0
                for j in range(self.A.shape[0]):
                    alpha[i] += p[j] * self.A[j][i] * self.B[i][ot]
            p = np.copy(alpha)
        return np.sum(alpha)

    def __viterbi(self, seq):
        """
        vitebi算法，用于求取最大概率的分词序列。
        :Parameters:
            - seq: 观测序列
        :Returns:
            - 返回概率和相应的状态序列
        """
        ot = ord(seq[0])
        assert(0 <= ot and ot <= self.m)
        alpha = 0.0
        beta = np.full(len(seq), self.STATE_P, dtype=np.int8)
        p = np.zeros(self.A.shape[0], dtype=np.float)

        # p_i(t): 序列为x1~xt，且状态为z1~zt且，且状态zt=i时的概率
        # 初始状态到seq[0]
        for i in range(self.A.shape[0]):
            p[i] = self.Pi[i] * self.B[i][ot]
        beta[0] = np.argmax(p)
        alpha = p[beta[0]]
            
        # seq[0]至seq[-1]
        for t in range(1, len(seq)):
            ot = ord(seq[t])
            assert(0 <= ot and ot <= self.m)
            for i in range(self.A.shape[0]):
                p[i] = alpha * self.A[beta[t-1]][i] * self.B[i][ot]
            beta[t] = np.argmax(p)
            alpha = p[beta[t]]
            # print(seq[t], list(map(lambda i: self.STATE_MAP[i], beta)), alpha)
            print(seq[t], self.STATE_MAP[beta[t]], alpha)
        return (alpha, beta)

    def test(self, test_data=''):
        """
        测试中文分词
        """
        if not self.__load():
            return False

        (alpha, beta) = self.__viterbi(test_data)
        seg = ''
        for k in range(len(test_data)):
            seg += test_data[k]
            if beta[k] == self.STATE_S or beta[k] == self.STATE_E:
                seg += ' '
        print(test_data)
        print(seg)

        return True


if __name__ == "__main__":
    print("Hidden Markov Model")
    hs = HmmSeg()

    # hs.train("training.utf8")
    # hs.train("./icwb2-data/training/msr_training.utf8")
    hs.test("我不觉泪如泉涌，一下子我理解了许多，明白了许多。")
    # print("我 不觉 泪如泉涌 ， 一下子 我 理解 了 许多 ， 明白 了 许多 。")
