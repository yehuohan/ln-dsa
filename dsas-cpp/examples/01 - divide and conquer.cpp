
#include <iostream>

namespace dsa
{

/*!
 * @addtogroup Example
 *
 * @{
 */

/*!
 * @brief 用迭代求序列的和
 *
 * @param a: 求和序列
 * @param lo,hi: 求和区间[lo,hi)
 * @return
 * @retval None
 */
int sum_iteration(int a[], int lo, int hi)
{
    int sum = 0;
    for(int k = lo; k < hi; k++)
    {
        sum += a[k];
    }
    return sum;
}

/*!
 * @brief 用递归求序列的和
 *
 * <pre>
 * Divide and Conquer: 分而治之
 * 大规模问题分成两个子问题：两个子问题规模相当
 *
 * </pre>
 *
 * @param a: 求和序列
 * @param lo,hi: 求和区间[lo,hi)
 * @return
 * @retval None
 */
int sum_divide_conquer(int a[], int lo, int hi)
{
    if(lo + 1 == hi) return a[lo];
    int mi = (lo + hi) / 2;
    return (sum_divide_conquer(a, lo ,mi) + sum_divide_conquer(a, mi, hi));
    // sum_dc(a, lo, mi)   : 子问题之一，求前半段区间之和
    // sum_dc(a, mi, hi)   : 子问题之二，求后半段区间之和
}

/*! @} */
} /* dsa */


int main()
{
    int a[1000];
    for(int k = 0; k < 1000; k ++)
    {
        a[k] = k;
    }

    int s1 = dsa::sum_iteration(a, 0, 1000);
    int s2 = dsa::sum_divide_conquer(a, 0, 1000);

    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
}
