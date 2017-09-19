
//==============================================================================
/*!
 * @file 01 - LCS.cpp
 * @brief longest common subsequence(最长公共子序列)
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#include <iostream>


//==============================================================================
/*!
 * @brief 通过递归求解LCS
 *
 * no consideration for complex situation
 *
 * @param a[] 序列a
 * @param n 序列a的长度
 * @param b[] 序列b
 * @param m 序列b的长度
 * @return LCS的长度
 * @retval None
 */
//==============================================================================
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


//==============================================================================
/*!
 * @brief 通过迭代求解LCS
 *
 * iteration algorithm of lcs
      d d a d
    a     1 
    d 1 1   2
    a     2
 * any equalpoint at the right-down of '1' is '2'
 *
 * @param a[] 序列a
 * @param n 序列a的长度
 * @param b[] 序列b
 * @param m 序列b的长度
 * @return
 * @retval None
 */
//============================================================================//
#include <vector>
typedef struct _EqualPoint
{
    int x;
    int y;
    _EqualPoint(int _x = 0, int _y = 0)
        :x(_x), y(_y){}
}EqualPoint;

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



int main()
{
    const int NUM = 100;
    char A[NUM] = "sidacticatypedecrea";
    int n = 0;
    while(A[n++] != '\0');
    char B[NUM] = "advantawhatswrongw";
    int m = 0;
    while(B[m++] != '\0');

    std::cout << "lcs_len_iteration: ";
    std::cout << lcs_len_iteration(A, n, B, m) << std::endl;

    std::cout << "lcs_len_recursion: ";
    std::cout << lcs_len_recursion(A, n, B, m) << std::endl;

    return 0;
}
