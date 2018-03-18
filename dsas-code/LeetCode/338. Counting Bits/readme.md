## Counting Bits
Given a non negative integer number num. For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their binary representation and return them as an array.

 - Example:

For num = 5 you should return [0,1,1,2,1,2].

 - Follow up:

It is very easy to come up with a solution with run time O(n*sizeof(integer)). But can you do it in linear time O(n) /possibly in a single pass?
Space complexity should be O(n).
Can you do it like a boss? Do it without using any builtin function like \_\_builtin\_popcount in c++ or in any other language.

 - Hint:

You should make use of what you have produced already.
Divide the numbers in ranges like [2-3], [4-7], [8-15] and so on. And try to generate new range from previous.
Or does the odd/even status of the number help you in calculating the number of 1s?

## Code

```
rcb[0] = 0;
rcb[1] = 1;
rcb[k] = rcb[k >> 1] + rcb[k & 1];

对k >> 1的理解:
  向右移一位，'1'的个数不变；
  向右移一位即除2，最终的结果不是0就是1，所以要先给rcb[0]和rcb[1]赋值；

对k & 1的理解：
  向右移一位，则最低的一位将丢弃，如果丢弃的是'1'，则要加上；
```
