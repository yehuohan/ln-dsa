
#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        if (array.empty()) return false;
        int rows = array.size();
        int cols = array[0].size();
        //if (array[0][0] > target) return false;
        //if (array[rows-1][cols-1] < target) return false;

        int r,c;
#if 0
        // 从左下角开始
        r = rows - 1; c = 0;
        while (r > 0 && c <= cols)
        {
            if (array[r][c] < target) c ++;
            else if (array[r][c] > target) r --;
            else return true;
        }
#endif
#if 0
        // 从右上角开始
        r = 0; c = cols - 1;
        while (r < rows && c >= 0)
        {
            if (array[r][c] < target) r ++;
            else if (array[r][c] > target) c --;
            else return true;
        }
#endif

#if 1
        int lo, hi, mi;
        // 从右上角开始
        r = 0; c = cols - 1;
        while (r < rows && c >= 0)
        {
            // 二分：返回不大于target的元素下标
            // 按列二分
            lo = 0; hi = c;
            while (lo < hi)
            {
                mi = (lo + hi) / 2;
                if (array[r][mi] < target) lo = mi + 1;
                else if (array[r][mi] > target) hi = mi;
                else return true;
            }
            c = mi;

            // 按行二分
            lo = r; hi = rows - 1;
            while (lo < hi)
            {
                mi = (lo + hi) / 2;
                if (array[mi][c] < target) lo = mi + 1;
                else if (array[mi][c] > target) hi = mi;
                else return true;
            }
            r = mi + 1;
        }
#endif

        return false;
    }
};

int main()
{
    std::vector<std::vector<int>> array(4, std::vector<int>(4));
    int target;
    target = 10;
    array[0][0] = 1; array[0][1] = 2; array[0][2] = 8; array[0][3] = 9;
    array[1][0] = 2; array[1][1] = 4; array[1][2] = 9; array[1][3] = 12;
    array[2][0] = 4; array[2][1] = 7; array[2][2] =10; array[2][3] = 13;
    array[3][0] = 6; array[3][1] = 8; array[3][2] =11; array[3][3] = 15;

    Solution su;
    bool flg = su.Find(target, array);
    std::cout << (flg ? "True" : "False") << std::endl;
    return 0;
}
