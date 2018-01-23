## Partition Labels
A string S of lowercase letters is given. We want to partition this string into as many parts as possible so that each letter appears in at most one part, and return a list of integers representing the size of these parts.

 - Example 1:

```
Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.
```

 - Note:

S will have length in range [1, 500].

S will consist of lowercase letters ('a' to 'z') only.


## Code

### 分割与合并法 

 - 极端情况

```
"abcde"
最多能分开5个部分
["a", "b", "c", "d", "e"]
```

 - 合并的两种情况

```
"abcade"
分到第2个"a"时，需要将前面的部分合并，然后继续分
["a", "b", "c"] => ["abca", "d", "e"]

"abcbde"
分到第2个"b"时，需要将前面从"b"开始的部分合并，然后继续分
["a", "b", "c"] => ["a", "bcb", "d", "e"]
```

### 下标计算法

S 的字母字为"a~z"，先求出每个字母的最大下标pos：

```
"abcdeakkbiiii"
pos['a'] = 5，分割的第一部分 至少为S[0:5]
pos['b'] = 8，分割的第一部分更新成 至少为S[0:8]
pos['i'] = 12，分割的第二部分 至少为S[9:12] 
```
