
//==============================================================================
/*!
 * @file 04 - symbol_match.cpp
 * @brief match symbol link parenthness
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
 * @brief 括号匹配
 *
 * 对expr[lo, hi)进行括号匹配
 *
 * @param expr: 进行匹配的表达式
 * @param lo: 匹配区间，>=lo
 * @param hi: 匹配区间，<hi
 * @return
 * @retval None
 */
//==============================================================================
bool match_parenthness(const char expr[], int lo, int hi)
{
    dsa::Stack<char> s;
    for(int k = lo; k < hi; k++)
    {
        if('(' == expr[k])
            s.push(expr[k]);
        else if(!s.is_empty())
            s.pop();
        else
            return false;
    }
    return s.is_empty();
}



//==============================================================================
/*!
 * @brief 判断是否为符号对左端
 *
 * @param a: 需要判断的字符
 * @return true or false
 * @retval None
 */
bool is_match_left(char a)
{
    if ('{' == a
     || '(' == a
     || '<' == a
     || '[' == a
     )
    {
        return true;
    }
    else
        return false;
}
/*!
 * @brief 判断两个字符是否为符号对
 *
 * @param a,b : 需要判断的字符
 * @return true or false
 * @retval None
 */
bool is_match(char a, char b)
{
    switch (a)
    {
        case '{':
            return b=='}' ? true : false;
        case '(':
            return b==')' ? true : false;
        case '<':
            return b=='>' ? true : false;
        case '[':
            return b==']' ? true : false;
    }
}
/*!
 * @brief 符号匹配
 *
 * @param expr: 进行匹配的表达式
 * @param lo: 匹配区间，>=lo
 * @param hi: 匹配区间，<hi
 * @return true or false
 * @retval None
 */
//==============================================================================
bool match_symbol(const char expr[], int lo, int hi)
{
    dsa::Stack<char> s;
    for(int k = lo; k < hi; k++)
    {
        if(is_match_left(expr[k]))
            s.push(expr[k]);
        else if(!s.is_empty())
        {
            if(!is_match(s.pop(), expr[k])) 
                return false;
        }
        else
            return false;
    }
    return s.is_empty();
}


int main(void)
{
    std::cout << std::endl;

    const char expr1[100] = "(())()(())";
    std::cout << "expr: " << expr1 << std::endl;
    if(match_parenthness(expr1, 0, 10))
        std::cout << "Parenthness: True" << std::endl;
    else
        std::cout << "Parenthness: False" << std::endl;

    std::cout << std::endl;

    const char expr2[100] = "<({})([])><(())>";
    std::cout << "expr: " << expr2 << std::endl;
    if(match_symbol(expr2, 0, 16))
        std::cout << "Parenthness: True" << std::endl;
    else
        std::cout << "Parenthness: False" << std::endl;

    std::cout << std::endl;

    return 0;
}
