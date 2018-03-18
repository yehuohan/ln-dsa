
import os
from functools import cmp_to_key

class Solution:
    def comp(self, a, b):
        """ 比较 a < b : -1 """
        if a[1] < b[1]:
            return -1
        if a[1] == b[1] and a[0] > b[0]:
            return -1
        if a[0] == b[0] and a[1] == b[1]:
            return 0
        return 1

    def intersectionSizeTwo(self, intervals):
        """
        :type intervals: List[List[int]]
        :rtype: int
        """
        if len(intervals) == 0:
            return 0
        # 两种sort，任选其一
        intervals.sort(key = cmp_to_key(lambda a,b :self.comp(a,b)))
        #intervals.sort(key = lambda x : x[1])
        i = intervals[0][1] - 1
        j = intervals[0][1]
        res = 2
        for it in intervals:
            if i < it[0] and it[0] <= j:
                res += 1
                i = j
                j = it[1]
            elif j < it[0]:
                res += 2
                i = it[1] - 1
                j = it[1]
        return res

if __name__ == "__main__":
    intervals = [[1,3], [1,4], [2,5], [3,5]]
    su = Solution()
    print(su.intersectionSizeTwo(intervals))
