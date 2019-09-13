## Largest Plus Sign
In a 2D grid from (0, 0) to (N-1, N-1), every cell contains a 1, except those cells in the given list mines which are 0. What is the largest axis-aligned plus sign of 1s contained in the grid? Return the order of the plus sign. If there is none, return 0.

An "axis-aligned plus sign of 1s of order k" has some center grid[x][y] = 1 along with 4 arms of length k-1 going up, down, left, and right, and made of 1s. This is demonstrated in the diagrams below. Note that there could be 0s or 1s beyond the arms of the plus sign, only the relevant area of the plus sign is checked for 1s.

Examples of Axis-Aligned Plus Signs of Order k:

```
Order 1:
000
010
000

Order 2:
00000
00100
01110
00100
00000

Order 3:
0000000
0001000
0001000
0111110
0001000
0001000
0000000
```

Example 1:

```
Input: N = 5, mines = [[4, 2]]
Output: 2
Explanation:
11111
11111
1*111
***11
1*011
In the above grid, the largest plus sign can only be order 2.  One of them is marked in '*'.
```

Example 2:

```
Input: N = 2, mines = []
Output: 1
Explanation:
There is no plus sign of order 2, but there is of order 1.
```

Example 3:

```
Input: N = 1, mines = [[0, 0]]
Output: 0
Explanation:
There is no plus sign, so return 0.
```

Note:

```
N will be an integer in the range [1, 500].
mines will have length at most 5000.
mines[i] will be length 2 and consist of integers in the range [0, N-1].
(Additionally, programs submitted in C, C++, or C# will be judged with a slightly smaller time limit.)
```


## Code

### 递归算法（超时）

递归基：

```
N = 1:
-            -
0            1
-            -
order = 0    order = 1

N = 2:

--
00           --
00           其它类型
--           --
order = 0    order = 1
```

递归：

```
N为奇数：
-----
  1
11111
  1
-----
看是否符合Axis-Aligned Plus Signs的形状：
是，则返回order
否，继续按下列方式递归求解：
  无论N为偶数还是奇数
  ----
  1111
  1111
  1111
  1111
  ----
  分成四部分，原点为[0,0] [0,1] [1,0] [1,1]，长度为N-1，递归求解。
```


### 动态归化

 - 核心代码：
```
grid：非0即N
for (int i = 0; i < N; i ++)
{
    int l = 0, r = 0, u = 0, d = 0;
    for (int j = 0, k = N - 1; j < N; j ++, k--)
    {
        // i 为行，则：
        // j 左 -> 右
        // k 右 -> 左
        grid[i][j] = std::min(grid[i][j], l = ((grid[i][j] == 0) ? 0 : l + 1));
        grid[i][k] = std::min(grid[i][k], r = ((grid[i][k] == 0) ? 0 : r + 1));

        // i 为列，则：
        // j 上 -> 下
        // k 下 -> 上
        grid[j][i] = std::min(grid[j][i], u = ((grid[j][i] == 0) ? 0 : u + 1));
        grid[k][i] = std::min(grid[k][i], d = ((grid[k][i] == 0) ? 0 : d + 1));
    }
}

N = 3，i为行：
grid          : 333    333    333
左->右的grid  : 1   => 12  => 123 => '333'可形成最大2 order的"十字"
左<-右的grid  :   1     21    321     同理，i为列的'333'，也可以形成最大2 order的"十字"；
min之后的grid : 131    121    121

行列取min后，可得到：
i=0和i=1的图解：第0行与第1列的grid[0][1]取min后，变成了1
       i = 0     i = 1     i = 2
333     121       111       111
333 =>  233   =>  121   =>  121
333     133       11        111


N=3的几个例子：
333    111
303 => 101
333    111

033    011
333 => 121
333    111

333    111
033 => 011
333    111
```
