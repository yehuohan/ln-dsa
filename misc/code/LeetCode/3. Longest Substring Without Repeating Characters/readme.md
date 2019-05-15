
## Longest Substring Without Repeating Characters
Given a string, find the length of the longest substring without repeating characters.

Examples:

```
Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
```

## Code

遍历S，同时将S的每个字符和其下表放到映射表pos中：pos[ch] = index。
通过判断pos[ch]是否存，即可判断ch是否在S的前缀中。
 - 在，则移动S前缀的起始点；
 - 不在，则Longest substing长度加1；

