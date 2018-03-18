## Set Intersection Size At Least Two
An integer interval [a, b] (for integers a < b) is a set of all consecutive integers from a to b, including a and b.

Find the minimum size of a set S such that for every integer interval A in intervals, the intersection(交集) of S with A has size at least 2.

 - Example 1:

```
Input: intervals = [[1, 3], [1, 4], [2, 5], [3, 5]]
Output: 3
Explanation:
Consider the set S = {2, 3, 4}.  For each interval, there are at least 2 elements from S in the interval.
Also, there isn't a smaller size set that fulfills the above condition.
Thus, we output the size of this set, which is 3.

```

 - Example 2:

```
Input: intervals = [[1, 2], [2, 3], [2, 4], [4, 5]]
Output: 5
Explanation:
An example of a minimum sized set is {1, 2, 3, 4, 5}.
```

 - Note:
    - intervals will have length in range [1, 3000].
    - intervals[i] will have length 2, representing some integer interval.
    - intervals[i][j] will be an integer in [0, 10^8].

## Code

 - 先排序

```
按右端升序，右端相同时按左端降序
  [   ]
    [    ]
[        ]
   [       ]
           [      ]

```

 - 计算Size

```
基本计算：

A [     ]
对一个interval，其Size = 2；

A: [   ij]
B:   [0     ]
对两个交集点>=2的interval，其Size = 2；
而因为排序关系，若是右端相同，则必有两个以上的交集点。
```

 - 贪心解法

```
(1) 普遍情况：
A: [   ij]           A: [    i]
B:     [0    ]  =>   B:     [    j]     =>   B: [    i]   
                     C:        [0    ]       C:    [    j]
                                             D:    [0    ]
A,B至少一个交集点，i < B[0] <= j；
  则Size增加1；（A,B要取一个公共点，才使Size最小）
  且i变成A的最右端的点，j变成B的最右端的点；

B,C至少一个交集点，但A,C没有交集点，i < C[0] <= j；
  则Size增加1；（A,B要取一个公共点，且B,C要取至少一个公共点，才使Size最小）
  且i变成B的最右端的点，j变成C的最右端的点；

若是D[0] <= i，则；
  C,D至少有一个交集点，B,D至少有一个交集点，所以Size不用增加。


(2) 最理想的情况：
A: [ ij]        =>    A: [   ]     
B:      [0  ]         B:      [  ij]

A,B没有交集，j < B[0]；
则Size(A)+Size(B) = 2+2，且i,j改成B的最右端的两个点；
```
