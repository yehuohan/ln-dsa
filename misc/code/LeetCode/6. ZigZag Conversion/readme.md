## ZigZag Conversion

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

```
P   A   H   N
A P L S I I G
Y   I   R
```

And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:

```
string convert(string text, int nRows);
```

`convert("PAYPALISHIRING", 3)` should return "PAHNAPLSIIGYIR".

## Code

 ZigZag的理解

 ```
  s = "abcdefg", row = 4

  按ZigZag排序：

  a  g
  b f
  ce
  d

  按行组合：
  agbfced
 ```
