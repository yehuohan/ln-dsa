
#include <iostream>
#include <cmath>
#include "../stack.h"
#include "operator_calc.h"

namespace dsa
{

/*!
 * @addtogroup Example
 *
 * @{
 */

/** 判断是否为数字字符 */
bool is_digit(char ch) {return (('0' <= ch && ch <= '9') ? true :false);}

/*!
 * @brief 从字符串中解析出一个数
 *
 * <pre>
 *
 *  "1234 + 21"
 *   a   b
 *
 * 解析前： str指向a
 * 解析后： str指向b
 *
 * </pre>
 *
 */
float read_number(char*& str)
{
    unsigned int t = 0;
    while(is_digit(*str))
    {
        t *= 10;
        t += (*str) - '0';
        str ++;
    }
    return float(t);
}


/*!
 * @brief 直接计算中缀表达式结果
 *
 * <pre>
 * 获取中缀表达式的计算结果
 *
 * 波兰表达式         ： 二元运算符置于运算数之前，也即前缀表达式
 * 中缀表达式         ： 二元运算符置于运算符之间
 * 逆波兰表达式（RPN) ： 二元运算符置于运算数之后，也即后缀表过式
 * </pre>
 *
 * @param str: 中缀表过达式
 * @return
 * @retval None
 */
float evaluate_infix(char* str)
{
    dsa::Stack<float> opnd;     // 运算数 operand
    dsa::Stack<char>  optr;     // 运算符 operator

    optr.push('\0');
    while(!optr.is_empty())     // 当运算符为空时，即已完成所有运算
    {
        if(is_digit(*str))
            opnd.push(read_number(str));    // 读入运算数，这里会向前移动指向字符指针的位置
        else
        {
            // 读入运算符
            switch(dsa::optr_get_priority(optr.top(), *str))
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

                // optr.top() > *str
                // 当前运算符优先级低，对栈中的运算符进行运算
                case '>':
                    dsa::OperatorCalc op(optr.pop());
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


/*!
 * @brief 将中缀表达式转化成逆波兰(RPN)表达式
 *
 * <pre>
 *
 * 转换原理： (a+b)  ->  ab+ ， 即将运算符放到括号外。
 * a,b可以为数值，或其它正确的中缀表达式，依次递归转换，即可将中缀表达式转成RPN。
 *
 * infix : (0! + 1) ^ (2 * 3! + 4 - 5)
 * add   : {([0!] +1) ^ ([(2 * [3!]) +4] - 5)}
 * rpn   :    0!   1+      2    3!  * 4 + 5 - ^
 *
 * </pre>
 *
 * @param str: 中缀表达式
 * @param rpn: 逆波兰(RPN)表达式
 * @return
 * @retval None
 */
void convert_notation(char* str, char*& rpn)
{
    dsa::Stack<char>  optr;     // 运算符 operator

    optr.push('\0');
    while(!optr.is_empty())
    {
        if(is_digit(*str))
            *rpn++ = *str++;
        else
        {
            // 读入运算符
            switch(dsa::optr_get_priority(optr.top(), *str))
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

/*!
 * @brief 计算逆波兰(RPN)表达式结果
 *
 * 一般先用convert_notation函数，将中缀表达式转成RPN表达式，再计算RPN表达式结果。
 *
 * @param str: 逆波兰(RPN)表达式
 * @return
 * @retval None
 */
float evaluate_rpn(char* str)
{
    dsa::Stack<float>  s;
    while(*str != '\0')
    {
        if(is_digit(*str))
            s.push(read_number(str));       // 操作数入栈
        else
        {
            dsa::OperatorCalc op(*str);     // 运算符直接计算
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

/*! @} */

} /* dsa */ 


int main(void)
{
    //char* str = "12845+22*(28-285)+9!/3";   // 7191 + 9!/3 = 128151
    char* str = "(0!+1)^(2*3!+4-5)";            // 2^11 = 2048
    char* s = str;

    s = str;
    std::cout << "Infix:  " << str << std::endl;
    std::cout << "Result: " << dsa::evaluate_infix(s) << std::endl;

    char  rpn[100];
    char* r = rpn;
    dsa::convert_notation(s, r);
    r = rpn;
    std::cout << std::endl;
    std::cout << "RPN:    " << rpn << std::endl;
    std::cout << "Result: " << dsa::evaluate_rpn(r) << std::endl;

    return 0;
}
