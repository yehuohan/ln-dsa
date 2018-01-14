## Special Binary String

Special binary strings are binary strings with the following two properties:

The number of 0's is equal to the number of 1's.
Every prefix of the binary string has at least as many 1's as 0's.

Given a special string S, a move consists of choosing two consecutive, non-empty, special substrings of S, and swapping them. (Two strings are consecutive if the last character of the first string is exactly one index before the first character of the second string.)

At the end of any number of moves, what is the lexicographically largest resulting string possible?

Example 1:

```
Input: S = "11011000"
Output: "11100100"
Explanation:
The strings "10" [occuring at S[1]] and "1100" [at S[3]] are swapped.
This is the lexicographically largest string possible after some number of swaps.
```

Note:
 - 1. S has length at most 50.
 - 2. S is guaranteed to be a special binary string as defined above.

## Code

首先得看懂问题，我经过多次错误的Submit后，才完明白题目要我们做什么。

 - 首先明白什么是`Special String`
题中给出两点：1和0的数量相同；任何一个前缀 1的数量 >= 0的数量。
在Discuss的中`Think of it as Valid-Parentheses`（解题思路这是参考这的），对此有一个很好的理解：将 `10` 看成 `()`，这样， `Special String`就是一个`正确配对的括号字符串`。所以，也容易容知道，`Special String`必定是`1`开头，`0`结尾。

 - 然后明白一个`move`有哪些步骤
将 10 换成 括号 后，就很好理解了，`move`即是： 将 `两个相邻的`、`能正确配对的括号字符串` 对调（在下面示例中，将带下划线的括号对调）。

```
Input:  "11011000" = "( () (()) )"
                        -- ----
Output: "11100100" = "( (()) () )"
                        ---- --
```

 - 最后要知道要做什么

题目即是问：在`Special String`做任意次`move`的过程中，求出`Special String`作为二进制数值的最大值是多少？

而我们需要做的，简单来说：通过`move`操作，使用`Special String`的二进制数值达到最大。即使得 `1` 尽可能在左侧。

 - 解题思路

简单来说，就是：对所有`sub-Special String`进行降序排序（我们估且称之为`reorder`）。如下所示：

```
排序前：
10 1100 111000
() (()) ((()))

排序后：
111000 1100 10
((())) (()) ()
```

要注意的是，如果`sub-Special String`中也含有`sub-Special String`，就需要递归`reorder`。则递归基为：`sub-Special String`为`10`即`()`。

例如，下而的`sub-Special String`均要继续递归reorder：

```
111000
((()))

11011000
(()(()))

```

代码就不细讲了，基本就是查找子串、字符比较排序什么的，主要还是理解递归的逻辑。
