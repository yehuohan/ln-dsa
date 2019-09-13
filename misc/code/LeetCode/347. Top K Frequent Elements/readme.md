## Top K Frequent Elements

Given a non-empty array of integers, return the k most frequent elements.

For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].

Note:
 - You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
 - Your algorithm's time complexity must be better than O(n log n), where n is the array's size.

## Code
建立<number, frequency>的Hash表，以frequency为下标将number插入到一个数组中，则下标最大的就是频序最高的（注意相同频率的问题）。
