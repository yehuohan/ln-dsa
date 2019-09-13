## Two Sum
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

 - Example:

```
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
```

## Code
 - 蛮力法：

```
for a in nums:
    for b in nums:
        if a+b = target
            return [a, b]

```

 - 利用HashTable：

```
for index in nums:
    key = nums[index]
    val = index
    push (key, val) to hash table
for val in nums:
    key = target - val
    find key in hash table
```
