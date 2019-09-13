## Median of Two Sorted Arrays

There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

 - Example 1:

```
nums1 = [1, 3]
nums2 = [2]
```

The median is 2.0

 - Example 2:

```
nums1 = [1, 2]
nums2 = [3, 4]
```

The median is (2 + 3)/2 = 2.5

## Code

 - 蛮力算法
合并列表再python sort，然后返回中位数；
或者使用归并算法合并列表，然后返回中位数。

 - 根据中位数定义

对一个序列S，分割成左右两部分L,R，若有：

```
  len(L) = len(R)
  max(L) <= len(R)
```

则中位数为： (max(L)+min(R)) / 2

实现：

```
  设有序序列为：
  A: [  i ]     len(A) = m
  B: [   j   ]  len(B) = n > m

  若i为A中的下标，当len(L)=len(R)时，B中的下标j为：
  j = (m+n)/2-i

  则有：
  A[i-1] <= A[i]
  B[j-1] <= B[j]

  若有：
  B[j-1] <= A[i]
  A[i-1] <= B[j]
  则中位数为：
  (max(A[i-1], B[j-1]) + min(A[i], B[j])) / 2
```
