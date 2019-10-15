
#include <iostream>

namespace dsa
{

/*!
 * @addtogroup Example
 *
 * @{
 */

/*!
 * @brief 递归求取
 *
 * @param n: 第n个Fibonacci数
 * @return
 * @retval None
 */
int fib_recursion(int n)
{
    return (n < 2) ? n : fib_recursion(n-1) + fib_recursion(n-2);
    // 自顶(n-1, n-2)而下递归
    // 计算过程中，产生大量的重复数据(冗余)
}

/*!
 * @brief 迭代求取
 *
 * @param n: 第n个Fibonacci数
 * @return
 * @retval None
 */
int fib_iteration(int n)
{
    int f = 0;
    int g = 1;
    while(n-- > 0)
    {
        g = g + f;
        f = g - f;
        // 自底(0, 1)而上迭代计算
    }
    return g;
}

/*! @} */
} /* dsa */


int main()
{
    int N = 45;
    std::cout << "N: " << N << std::endl;

    std::cout << "fib_iteration(N): " << dsa::fib_iteration(N) << std::endl;
    std::cout << "fib_recursion(N): " << dsa::fib_recursion(N) << std::endl;
}
