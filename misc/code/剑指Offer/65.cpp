
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using std::string;
using std::vector;

class Solution {
public:
    bool hasPath(char* matrix, int rows, int cols, char* str)
    {
        std::vector<bool> flg(rows * cols, false);
        for (int i = 0; i < rows; i ++)
        {
            for (int j = 0; j < cols; j ++)
            {
                if (is_path(matrix, rows, cols, i, j, str, flg))
                    return true;
            }
        }
        return false;
    }

    /*!
     * @brief 判断路径
     *
     * @param matrix: 字符矩阵
     * @param rows,cols: 字符矩阵行列大小
     * @param i,j: 当前字符位置
     * @param str: 字符路径
     * @param flg: 字符是否被访问过
     * @return
     * @retval None
     */
    bool is_path(char* matrix, int rows, int cols,
            int i, int j,
            char* str, std::vector<bool>& flg)
    {
        if (*str == '\0') return true;

        int index = i * cols + j;
        if (i < 0 || i >= rows ||j < 0 || j >= cols     // 坐标超范围
          ||matrix[index] != *str                       // 字符不在路径str中
          ||flg[index] == true)                         // 字符已经置于路径str中
            return false;
        flg[index] = true;
        if (   is_path(matrix, rows, cols, i-1, j, str+1, flg)
            || is_path(matrix, rows, cols, i+1, j, str+1, flg)
            || is_path(matrix, rows, cols, i, j-1, str+1, flg)
            || is_path(matrix, rows, cols, i, j+1, str+1, flg))
            return true;
        flg[index] = false;
        return false;
    }
};

int main()
{
    Solution su;
    std::cout << su.hasPath("ABCESFCSADEE",3,4,"ABCCED") << std::endl;
}
