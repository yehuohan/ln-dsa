
## Interger Break
Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers. Return the maximum product you can get.

For example, given n = 2, return 1 (2 = 1 + 1); given n = 10, return 36 (10 = 3 + 3 + 4).

Note: You may assume that n is not less than 2 and not larger than 58.

## Code

```
ib(2) = 1*1 = 1;
ib(3) = 1*2 = 2;
ib(4) = 2*2 = 4;
ib(5) = 3*2 = 6;
ib(6) = 3*3 = 9
ib(7) = 3*4 = 3*2*2 = 12
ib(8) = 3*3*2 = 18
ib(9) = 3*3*3 = 27
```
当基本加法因子 > 4时，整数分解相乘后才会变得更大；

所以最小的加法因子只能为3和4（或2，因为2*2=4），即不能再对2和3分解；

再看ib(7)到ib(10)，基本加法因子3越多越好，不够3时，再用4或2分解。
