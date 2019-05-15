
class Solution:
    def findMedian_sort(self, nums1, nums2):
        """
        使用python的sort
        """
        nums = nums1 + nums2
        nums.sort()
        n = len(nums)
        if n & 1:       
            return nums[n//2]
        return (nums[n//2] + nums[n//2-1])/2

    def findMedian_merge(self, nums1, nums2):
        """
        使用归并算法，合并列表
        """
        n, m = len(nums1), len(nums2)
        i, j = 0, 0
        nums = []
        while i < n and j < m:
            if nums1[i] < nums2[j]:
                nums.append(nums1[i])
                i = i + 1
            else:
                nums.append(nums2[j])
                j = j + 1
        while i < n:
            nums.append(nums1[i])
            i = i + 1
        while j < m:
            nums.append(nums2[j])
            j = j + 1
        if (n+m) & 1:       
            return nums[(n+m)//2]
        return (nums[(n+m)//2] + nums[(n+m)//2-1])/2

    def findMedian_median(self, nums1, nums2):
        # 使nums1序列 短于 nums2序列
        m, n = len(nums1), len(nums2)
        if m > n:
            nums1, nums2, m, n = nums2, nums1, n, m
        if m == 0:
            if n & 1:
                return nums2[n//2]
            return (nums2[n//2]+nums2[n//2-1])/2

        # 寻找满足len(L)=len(R)且max(L)<=min(R)的i,j
        imin, imax, half_len = 0, m, (m+n+1)//2
        while imin <= imax:
            i = (imin + imax) // 2
            j = half_len - i

            # A [   i   ]
            # B [     j   ]
            # 条件： A[i-1] <= A[i] and A[i-1] <= B[j]
            #        B[j-1] <= A[i] and B[j-1] <= B[j]
            if i < m and nums2[j-1] > nums1[i]:
                imin = i + 1
            elif i > 0 and nums1[i-1] > nums2[j]:
                imax = i - 1
            else:
                if i == 0: max_left = nums2[j-1]
                elif j == 0: max_left = nums1[i-1]
                else: max_left = max(nums1[i-1], nums2[j-1])

                if (m+n) % 2 == 1:
                    return max_left

                if i == m: min_right = nums2[j]
                elif j == n: min_right = nums1[i]
                else: min_right = min(nums1[i], nums2[j])

                return (max_left + min_right) / 2

    def findMedianSortedArrays(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        #return self.findMedian_sort(nums1, nums2)
        # return self.findMedian_merge(nums1, nums2)
        return self.findMedian_median(nums1, nums2)


if __name__ == "__main__":
    su = Solution()
    a = [4,5,6,8,9]
    b = [2,4,6,7,8,9,12,15]
    print(su.findMedianSortedArrays(a,b))
