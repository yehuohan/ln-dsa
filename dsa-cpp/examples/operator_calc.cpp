
#include "operator_calc.h"

namespace dsa
{

/** 运符符优先级列表，“行”为计算式中的前一个运算符， “列”为当前运算符 */
const char optr_priority_table[N_OP][N_OP] = {
    //        +    -    *    /    ^    !    (    )   \0
    /* + */ {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
    /* - */ {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
    /* * */ {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    /* / */ {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    /* ^ */ {'>', '>', '>', '>', '>', '<', '<', '>', '>'},
    /* ! */ {'>', '>', '>', '>', '>', '>', ' ', '>', '>'},
    /* ( */ {'<', '<', '<', '<', '<', '<', '<', '=', ' '},
    /* ) */ {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    /*\0 */ {'<', '<', '<', '<', '<', '<', '<', ' ', '='},
};

/*!
 * @brief 获取运算符在优先列表中的下标
 *
 * @param ch: 运算符
 * @return
 * @retval None
 */
unsigned int optr_get_index(char ch)
{
    switch (ch)
    {
        case '+': return 0; break;
        case '-': return 1; break;
        case '*': return 2; break;
        case '/': return 3; break;
        case '^': return 4; break;
        case '!': return 5; break;
        case '(': return 6; break;
        case ')': return 7; break;
        case '\0': return 8; break;
    }
}

/*!
 * @brief 获取两个运算符，在优先级列表中的优先级符号
 *
 * @param ch1,ch2: 运算符
 * @return
 * @retval None
 */
char optr_get_priority(char ch1, char ch2)
{
    return optr_priority_table[optr_get_index(ch1)][optr_get_index(ch2)];
}


/*!
 * @brief 获取运算符类型
 *
 * @param None
 * @return
 * @retval 0: 不是运算符
 * @retval 1: 一元运算符
 * @retval 2: 二元运算符
 * @retval 3: 三元运算符
 */
int OperatorCalc::get_type()
{
    switch (this->m_ch)
    {
        case '!':
            return 1;
            break;

        case '+': 
        case '-':
        case '*':
        case '/':
        case '^': 
            return 2; 
            break;

        default:
            return 0;
    }
}

/*!
 * @brief factorial operating (阶乘运算)
 *
 * @param a: 计算阶乘的数
 * @return
 * @retval None
 */
float OperatorCalc::factorial(float a)
{
    int ret = 1;
    for(int k = a; k > 0; k --)
    {
        ret *= k;
    }
    return ret;
}

/*!
 * @brief 一元运算
 *
 * @param a: 一元运算操作数
 * @return
 * @retval None
 */
float OperatorCalc::calculate(float a)
{
    switch (this->m_ch)
    {
        case '!':
            return this->factorial(a);
            break;

    }
}

/*!
 * @brief 二元运算
 *
 * @param a,b: 二元运算操作数
 * @return
 * @retval None
 */
float OperatorCalc::calculate(float a, float b)
{
    switch (this->m_ch)
    {
        case '+': return (a+b); break;
        case '-': return (a-b); break;
        case '*': return (a*b); break;
        case '/': return (a/b); break;
        case '^': return (std::pow(a,b)); break;
    }
}

} /* dsa */ 
