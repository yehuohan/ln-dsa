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
