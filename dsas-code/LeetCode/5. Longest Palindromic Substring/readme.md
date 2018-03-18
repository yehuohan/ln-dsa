## Longest Palindromic Substring

Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example:

```
Input: "babad"

Output: "bab"
```

Note: "aba" is also a valid answer.


Example:

```
Input: "cbbd"

Output: "bb"
```

## Code

使用对称性判断回文，不断的更新最大回文子串的起止下标。
