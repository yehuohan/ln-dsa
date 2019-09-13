
class Solution:
    def expandPalindrome(self, s, l, r):
        """
        :type s:str
        :type l:left side
        :type r:right side
        :rtype: length of palindrome
        """
        while l >= 0 and r < len(s) and s[l] == s[r]:
            l = l - 1
            r = r + 1
        return r-l-1

    def findLP_BruteForce(self, s):
        # O(n^2)
        i,j = 0,-1
        for k in range(0, len(s)):
            len1 = self.expandPalindrome(s, k, k)
            len2 = self.expandPalindrome(s, k, k + 1)
            max_len = max(len1, len2)
            if max_len > j - i:
                i = k - (max_len-1)//2
                j = k + max_len//2 + 1
        return s[i:j]

    def longestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
        return self.findLP_BruteForce(s)

if __name__ == "__main__":
    su = Solution()
    s = "babad"
    print(su.longestPalindrome(s))
    print(s)
