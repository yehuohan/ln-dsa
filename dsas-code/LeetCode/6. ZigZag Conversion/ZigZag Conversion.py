
class Solution:
    def convert(self, s, numRows):
        """
        :type s: str
        :type numRows: int
        :rtype: str
        """
        if numRows == 1 or len(s) <= numRows:
            return s
        grid = [''] * numRows
        i, f = 0, True
        for ch in s:
            grid[i] += ch
            if i == 0:
                f = True
            if i == numRows-1:
                f = False
            i = (i + 1) if f else (i - 1)
        return ''.join(grid)

if __name__ == "__main__":
    su = Solution()
    s = "PAYPALISHIRING"
    print(s)
    print(su.convert(s, 3))
        
