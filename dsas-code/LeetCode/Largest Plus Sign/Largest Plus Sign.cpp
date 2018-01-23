
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
// 超时递归算法
#if(0)
    /** 求n行n列的最大order */
    int max_order(int n){return (n - 1)/2 + 1;}

    /** 计算grid的order */
    int calc_order(const std::vector<std::vector<int>>& grid, int x0, int y0, int len)
    {
        if (len == 1)
            return grid[x0][y0];
        if (len == 2)
        {
            if (grid[x0][y0] || grid[x0][y0+1] || grid[x0+1][y0] || grid[x0+1][y0+1]) return 1;
            else return 0;
        }

        // 奇数
        if (len&1)
        {
            // x for col, y for row
            int m = len / 2;
            int iu = 0, id = 0,il = 0,ir = 0;
            for (int k = 0; k < m; k ++)
            {
                if (!grid[y0+k    ][x0+m    ]) iu++;
                if (!grid[y0+m+1+k][x0+m    ]) id++;
                if (!grid[y0+m    ][x0+k    ]) il++;
                if (!grid[y0+m    ][x0+m+1+k]) ir++;
            }
            if (grid[y0+m][x0+m] && !iu && !id && !il && !ir)
                    return max_order(len);
        }
        // 偶数
        int r1 = calc_order(grid, x0  , y0  , len-1); if (r1 == max_order(len-1)) return r1;
        int r2 = calc_order(grid, x0  , y0+1, len-1); if (r2 == max_order(len-1)) return r2;
        int r3 = calc_order(grid, x0+1, y0  , len-1); if (r3 == max_order(len-1)) return r3;
        int r4 = calc_order(grid, x0+1, y0+1, len-1); if (r4 == max_order(len-1)) return r4;
        if (r1 < r2) r1 = r2;
        if (r1 < r3) r1 = r3;
        if (r1 < r4) r1 = r4;
        return r1;
    }

    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
        if (N == 0) return 0;

        // 生成grid
        std::vector<std::vector<int>> grid(N, std::vector<int>(N,1));
        for (auto &m : mines)
            grid[m[0]][m[1]] = 0;

        return calc_order(grid, 0, 0, N);
    }
#else
    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
        if (N == 0) return 0;

        // 生成grid
        std::vector<std::vector<int>> grid(N, std::vector<int>(N,N));
        for (auto &m : mines)
            grid[m[0]][m[1]] = 0;

        for (int i = 0; i < N; i ++)
        {
            int l = 0, r = 0, u = 0, d = 0;
            for (int j = 0, k = N - 1; j < N; j ++, k--)
            {
                // i as row
                // j = left to right
                // k = right to left
                grid[i][j] = std::min(grid[i][j], l = ((grid[i][j] == 0) ? 0 : l + 1));
                grid[i][k] = std::min(grid[i][k], r = ((grid[i][k] == 0) ? 0 : r + 1));
                // i as col
                // j = up to down
                // k = down to up
                grid[j][i] = std::min(grid[j][i], u = ((grid[j][i] == 0) ? 0 : u + 1));
                grid[k][i] = std::min(grid[k][i], d = ((grid[k][i] == 0) ? 0 : d + 1));
            }
        }

        int res = 0;
        for (int i = 0; i < N; i ++)
        {
            for (int j = 0; j < N; j ++)
            {
                res = std::max(res, grid[i][j]);
                std::cout << grid[i][j];
            }
            std::cout << std::endl;
        }
        return res;

    }
#endif
};

int main(void)
{
    Solution su;
    int N = 5;
    std::vector<std::vector<int> > mines;
    std::vector<int> vi(2);
    vi[0] = 2; vi[1] = 1; mines.push_back(vi);
    //vi[0] = 1; vi[1] = 4; mines.push_back(vi);
    //vi[0] = 2; vi[1] = 4; mines.push_back(vi);
    //vi[0] = 3; vi[1] = 2; mines.push_back(vi);
    //vi[0] = 4; vi[1] = 0; mines.push_back(vi);
    //vi[0] = 4; vi[1] = 3; mines.push_back(vi);
    int r = su.orderOfLargestPlusSign(N, mines);
    cout << "order: " << r << endl;
    return 0;
}
