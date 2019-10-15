
#include <iostream>
#include "../stack.h"

namespace dsa
{

/*!
 * @addtogroup Example
 *
 * @{
 */

/*!
 * @brief 进制转换
 *
 * @param s: 用栈保存进制转换结果
 * @param n: 需要转换的数
 * @param base: 转换进制基数
 * @return
 * @retval None
 */
void convert(dsa::Stack<char>& s, __int64 n, int base)
{
    static char digit[] =
    {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    while(n > 0)
    {
        s.push(digit[n % base]);
        n /= base;
    }
}

/*! @} */
} /* dsa */


int main(void)
{
    dsa::Stack<char> s;
    dsa::convert(s, 123481, 2);
    std::cout << std::endl;
    while(!s.is_empty())
    {
        std::cout << s.pop();
    }
    std::cout << std::endl;
    std::cout << std::endl;

    return 0;
}
