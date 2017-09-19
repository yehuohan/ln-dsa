
//==============================================================================
/*!
 * @file 04 - convert.cpp
 * @brief 进制转换
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#include <iostream>
#include "../stack.h"

//==============================================================================
/*!
 * @brief 进制转换
 *
 * @param s: 用栈保存进制转换结果
 * @param n: 需要转换的数
 * @param base: 转换进制基数
 * @return
 * @retval None
 */
//==============================================================================
void convert(dsa::stack<char>& s, __int64 n, int base)
{
    static char digit[] =
    {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    while(n > 0)
    {
        s.push(digit[n % base]);
        n /= base;
    }
}


int main(void)
{
    dsa::stack<char> s;
    convert(s, 123481, 2);
    std::cout << std::endl;
    while(!s.is_empty())
    {
        std::cout << s.pop();
    }
    std::cout << std::endl;
    std::cout << std::endl;

    return 0;
}
