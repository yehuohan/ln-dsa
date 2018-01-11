
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
 * @param n: 序列长度
 * @return
 * @retval None
 */
int sum_iteration(int a[], int n)
{
    int sum = 0;
    for(int k = 0; k < n; k++)
    {
        sum += a[k];
    }
    return sum;
}

/*!
 * @brief 用递归求序列的和
 *
 * <pre>
 * Decrease and Conquer: 减而治之
 * 大规模问题分成两个子问题：一个规模减小，一个为平常问题。
 * </pre>
 *
 * @param a: 求和序列
 * @param n: 序列长度
 * @return
 * @retval None
 */
int sum_decrease_conquer(int a[], int n)
{
    return (n < 1) ? 0 : (sum_decrease_conquer(a,n-1) + a[n-1]);
    // sum_de(a,n-1) : 子问题之一，规模减小，仍是同类问题，仍可调用自身解决
    // + a[n-1]      : 子问题这二，平常的加法问题
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

    int s1 = dsa::sum_iteration(a, 1000);
    int s2 = dsa::sum_decrease_conquer(a, 1000);

    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
}
