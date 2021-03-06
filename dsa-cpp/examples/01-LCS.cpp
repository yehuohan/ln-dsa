
#include <iostream>
#include <vector>
#include <algorithm>

namespace dsa
{

/*!
 * @addtogroup Example
 *
 * @{
 */

/*!
 * @brief 通过递归求解LCS (longest common subsequence(最长公共子序列))
 *
 * 不考虑复杂情况。
 *
 * @param a: 序列a
 * @param n: 序列a的长度
 * @param b: 序列b
 * @param m: 序列b的长度
 * @return LCS的长度
 * @retval None
 */
int lcs_len_recursion(char a[], int n, char b[], int m)
{
    // no length means that no element
    if(n < 1 || m < 1) return 0;

    if(a[n-1] == b[m-1])
    {
        // decrease and conquer(减而治之)
        return lcs_len_recursion(a, n-1, b, m-1) + 1;
    }
    else
    {
        // divide and conquer(分而治之)
        // 用递归容易理解，也容易编写代码
        // 但是，这里会产生大量重复计算数据，效率低下
        int d1 = lcs_len_recursion(a, n-1, b, m);
        int d2 = lcs_len_recursion(a, n , b, m-1);
        return (d1>d2 ? d1 : d2);
    }
}

/*!
 * @brief 坐标点结构体
 *
 */
typedef struct _EqualPoint
{
    int x,y;
    _EqualPoint(int _x = 0, int _y = 0) : x(_x), y(_y) {}
}EqualPoint;

/*!
 * @brief 通过迭代求解LCS
 *
 * <pre>
 * LCS迭代求取算法：
 * “行” 和 “列” 分别为表示两个序列，数字n代表第n个相同的字符。
 *
 *    d d a d
 *  a     1
 *  d 1 1   2
 *  a     2
 *
 * 任何在某个 '1' 的 右下方 的 EqualPoint 必定为 '2'。
 * </pre>
 *
 * @param a: 序列a
 * @param n: 序列a的长度
 * @param b: 序列b
 * @param m: 序列b的长度
 * @return
 * @retval None
 */
int lcs_len_iteration(char a[], int n, char b[], int m)
{
    std::vector<EqualPoint> vec_ep;
    int cnt = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(a[i] == b[j])
            {
                if(vec_ep.empty())
                {
                    cnt ++;
                    vec_ep.push_back(EqualPoint(i, j));
                }
                else
                {
                    int flg = 0;
                    for(unsigned int k = 0; k < vec_ep.size(); k++)
                    {
                        // 只要(i,j)在某一个EqualPoint的右下方，即是一个新的Common Subsequence Point
                        if(i > vec_ep[k].x && j > vec_ep[k].y)
                        {
                            cnt ++;
                            vec_ep.clear();
                            vec_ep.push_back(EqualPoint(i, j));
                            flg = 1;
                            break;
                        }
                    }
                    if(!flg) // i和j一直是递增的，故有 i > cx || j > cy
                    {
                        // 同一级的Common Subsequence Point
                        vec_ep.push_back(EqualPoint(i, j));
                    }
                }
            }
        }
    }
    return cnt;
}

/*!
 * @brief 通过动态求解LCS
 *
 * 一个数列S，如果分别是已知数列A,B...的子序列，且是所有符合此条件序列中最长的，
 * 则S称为已知序列的最长公共子序列。
 *
 * <pre>
 * sub[i][j]
 *      表示A[0~i]与B[0~j]的LCS的长度
 *      （A[i]或B[j]必定是LCS最后一个相同的字符）
 * same(i, j)
 *      A[i]等于B[j]时为1，否则为0
 *
 * sub[0][0] = same(0, 0)
 * sub[i][j] = max{ sub[i-1][j-1] + same(i,j),
 *                  sub[i-1][j],
 *                  sub[i][j-1] }
 * </pre>
 *
 * @param a: 序列a
 * @param n: 序列a的长度
 * @param b: 序列b
 * @param m: 序列b的长度
 * @return
 * @retval None
 */
int lcs_len_dynamic(char a[], int n, char b[], int m)
{
    int len = 0;
    int** sub = new int*[n];
    for (int k = 0; k < n; k ++)
        sub[k] = new int[m];

    for (int i = 0; i < n; i ++)
    {
        for (int j = 0; j < m; j ++)
        {
            if (i == 0 || j == 0)
                sub[i][j] = (a[i] == b[j]) ? 1 : 0;
            else
            {
                len = sub[i-1][j-1] + ((a[i] == b[j]) ? 1 : 0);
                len = std::max(len, sub[i-1][j]);
                len = std::max(len, sub[i][j-1]);
                sub[i][j] = len;
            }
        }
    }

    len = sub[n-1][m-1];
    for (int k = 0; k < n; k ++)
        delete[] sub[k];
    delete[] sub;
    return len;
}

/*! @} */
} /* dsa */


int main()
{
    const int NUM = 100;
    char A[NUM] = "sidacticatypedecrea";
    int n = 0;
    while(A[n++] != '\0');
    char B[NUM] = "advantawhatswrongw";
    int m = 0;
    while(B[m++] != '\0');

    std::cout << "lcs_len_dynamic: ";
    std::cout << dsa::lcs_len_dynamic(A, n, B, m) << std::endl;

    std::cout << "lcs_len_iteration: ";
    std::cout << dsa::lcs_len_iteration(A, n, B, m) << std::endl;

    std::cout << "lcs_len_recursion: ";
    std::cout << dsa::lcs_len_recursion(A, n, B, m) << std::endl;

    return 0;
}
