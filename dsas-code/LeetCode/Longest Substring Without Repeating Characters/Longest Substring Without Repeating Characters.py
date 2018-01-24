
class Solution:
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        if s == "":
            return 0
        mlen = 1
        ss = 0
        pos = {}
        for idx,ch in enumerate(s):
            if ch in pos:
                ss = max(ss, pos[ch] + 1)
            pos[ch] = idx
            mlen = max(mlen, idx + 1 - ss)
        return mlen

if __name__ == "__main__":
    su = Solution()
    print(su.lengthOfLongestSubstring("abba"))
