
//==============================================================================
/*
 * 获取中缀表达式的计算结果
 *
 * 波兰表达式         ： 二元运算符置于运算数之前，也即前缀表达式
 * 中缀表达式         ： 二元运算符置于运算符之间
 * 逆波兰表达式（RPN) ： 二元运算符置于运算数之后，也即后缀表过式
 */
//==============================================================================

#include <iostream>
#include <cmath>
#include "../stack.h"
#include "OperatorCalc.h"


//==============================================================================
/*!
 * @brief check whether char is between '0' and '9'
 *
 * @param ch the char to be checked
 * @return true or false
 * @retval None
 */
//==============================================================================
bool is_digit(char ch)
{
    return (('0' <= ch && ch <= '9') ? true :false);
}

//==============================================================================
/*!
 * @brief parse a number from string
 *
 * str will point the next char to the end the number chars afeter parsing.
 *
 * @param str pointer reference to the string
 * @return the number
 * @retval None
 */
//==============================================================================
float read_number(char*& str)
{
    int t = 0;
    while(is_digit(*str))
    {
        t *= 10;
        t += (*str) - '0';
        str ++;
    }
    return float(t);
}

//==============================================================================
/*!
 * @brief evaluate from infix-string
 *
 * @param str: infix-string
 * @return return the calculation result
 * @retval None
 */
//==============================================================================
float evaluate_infix(char* str)
{
    dsa::Stack<float> opnd;     // 运算数 operand
    dsa::Stack<char>  optr;     // 运算符 operator

    optr.push('\0');
    while(!optr.is_empty())     // 当运算符为空时，即已完成所有运算
    {
        if(is_digit(*str))
        {
            // 读入运算数，这里会向前移动指向字符指针的位置
            opnd.push(read_number(str));
        }
        else
        {
            // 读入运算符
            switch(get_optr_priority(optr.top(), *str))
            {
                // optr.top() <,=,> *str
                // 当前运算符优先级高，等待下一个运算数
                case '<':
                    optr.push(*str);    
                    str ++;
                    break;

                // '()' 或 '\0'
                // '('优先级最低，故其后的运算符优先得到计算
                // ')'到达时，'()'中的运算已经成了一个数值
                case '=':
                    optr.pop();
                    str ++;
                    break;

                // 当前运算符优先级低，对栈中的运算符进行运算
                case '>':
                    OperatorCalc op(optr.pop());
                    if(op.is_unary_op())
                    {
                        opnd.push(op.calculate(opnd.pop()));
                    }
                    else if(op.is_binary_op())
                    {
                        float op2 = opnd.pop();
                        float op1 = opnd.pop();
                        opnd.push(op.calculate(op1, op2));
                    }
            }
        }
    }
    return opnd.pop();
}


//==============================================================================
/*!
 * @brief convert infix to RPN
 *
 * 转换原理： (a+b)  ->  ab+ ， 即将运算符放到括号外
 * a,b可以为数值，或其它正确的中缀表达式，依次递归转换，即可将中缀表达式转成RPN
 * infix : (0! + 1) ^ (2 * 3! + 4 - 5)
 * add   : {([0!] +1) ^ ([(2 * [3!]) +4] - 5)}
 * rpn   :    0!   1+      2    3!  * 4 + 5 - ^
 *
 * @param str: infix string
 * @param rpn: rpn string
 * @return
 * @retval None
 */
//==============================================================================
void convert_notation(char* str, char*& rpn)
{
    dsa::Stack<char>  optr;     // 运算符 operator

    optr.push('\0');
    while(!optr.is_empty()) 
    {
        if(is_digit(*str))
        {
            *rpn++ = *str++;
        }
        else
        {
            // 读入运算符
            switch(get_optr_priority(optr.top(), *str))
            {
                case '<':
                    *rpn++ = ' ';           // 在上一个数字字符后添加空格，用于区分两个连续数字
                    optr.push(*str);    
                    str ++;
                    break;

                case '=':
                    optr.pop();
                    str ++;
                    break;

                case '>':
                    *rpn++ = optr.pop();    // 将上一个优先的运算符提到“括号”外
            }
        }
    }
}

//==============================================================================
/*!
 * @brief evaluate from rpn-string
 *
 * @param str: rpn-string
 * @return return the calculation result
 * @retval None
 */
//==============================================================================
float evaluate_rpn(char* str)
{
    dsa::Stack<float>  s;
    while(*str != '\0')
    {
        if(is_digit(*str))
        {
            s.push(read_number(str));
        }
        else
        {
            OperatorCalc op(*str);
            if(op.is_unary_op())
            {
                s.push(op.calculate(s.pop()));
            }
            else if(op.is_binary_op())
            {
                float op2 = s.pop();
                float op1 = s.pop();
                s.push(op.calculate(op1, op2));
            }
            str++;
        }
    }

    return s.pop();
}


int main(void)
{
    //char* str = "12845+22*(28-285)+9!/3";   // 7191 + 9!/3 = 128151 
    char* str = "(0!+1)^(2*3!+4-5)";            // 2^11 = 2048
    char  rpn[100];
    char* s = str;
    char* r = rpn;
    convert_notation(s, r);
    
    s = str;
    std::cout << "Infix:  " << str << std::endl;
    std::cout << "Result: " << evaluate_infix(s) << std::endl;

    r = rpn;
    std::cout << std::endl;
    std::cout << "RPN:    " << rpn << std::endl;
    std::cout << "Result: " << evaluate_rpn(r) << std::endl;

    return 0;
}
