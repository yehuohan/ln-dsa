
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using std::string;
using std::vector;

class Solution {
public:
    int movingCount(int threshold, int rows, int cols)
    {
        std::vector<bool> flg(rows*cols, false);
        return moving(threshold, rows, cols, 0, 0, flg);
    }

    int moving(int threshold, int rows, int cols,
            int i, int j, std::vector<bool>& flg)
    {
        int cnt = 0;
        if (0 <= i && i < rows && 0 <= j && j < cols        // 坐标在矩阵内
            && get_sum(i) + get_sum(j) <= threshold         // 满足“数位之和”条件
            && flg[i * cols + j] == false)                  // 未被统计过
        {
            flg[i * cols + j] = true;
            // 统计能进入的格子数
            cnt = 1
                + moving(threshold, rows, cols, i+1, j, flg)
                + moving(threshold, rows, cols, i-1, j, flg)
                + moving(threshold, rows, cols, i, j+1, flg)
                + moving(threshold, rows, cols, i, j-1, flg);
        }
        return cnt;
    }

    int get_sum(int k)
    {
        // 求“数位”之和
        int sum = 0;
        while (k)
        {
            sum += k % 10;
            k /= 10;
        }
        return sum;
    }
};

int main()
{

}
