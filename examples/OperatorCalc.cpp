
//==============================================================================
/*!
 * @file OperatorCalc.cpp
 * @brief 运算符计算类
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#include "OperatorCalc.h"



//==============================================================================
/*!
 * @brief report the type of operator
 *
 * @param None
 * @return
 * @retval 0 : is not calculation operator
 * @retval 1 : is unary operator
 * @retval 2 : is binary operator
 * @retval 3 : is ternary operator
 */
//==============================================================================
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

//==============================================================================
/*!
 * @brief factorial operating (阶乘运算)
 *
 * @param a parameter for factorial
 * @return result of factorial
 * @retval None
 */
//==============================================================================
float OperatorCalc::factorial(float a)
{
    int ret = 1;
    for(int k = a; k > 0; k --)
    {
        ret *= k;
    }
    return ret;
}

//==============================================================================
/*!
 * @brief unary operator calculation
 *
 * @param a parameter for operator
 * @return
 * @retval None
 */
//==============================================================================
float OperatorCalc::calculate(float a)
{
    switch (this->m_ch)
    {
        case '!':
            return this->factorial(a);
            break;

    }
}

//==============================================================================
/*!
 * @brief binary operator calculation
 *
 * @param a,b parameters for operator
 * @return
 * @retval None
 */
//==============================================================================
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




/** 优先级表，行 为计算式中的前一个运算符， 列 为当前运算符 */
const char table_optr_priority[N_OP][N_OP] = {
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

//==============================================================================
/*!
 * @brief get the char's index in supported operators
 *
 * @param ch get the index of ch
 * @return the index of ch
 * @retval None
 */
//==============================================================================
unsigned int get_optr_index(char ch)
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

//==============================================================================
/*!
 * @brief get the priority between two operators 
 *
 * @param ch1,ch2 two operators
 * @return the priority in from table_optr_priority
 * @retval None
 */
//==============================================================================
char get_optr_priority(char ch1, char ch2)
{
    return table_optr_priority[get_optr_index(ch1)][get_optr_index(ch2)];
}


