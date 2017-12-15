
//==============================================================================
/*!
 * @file OperatorCalc.h
 * @brief 运算符计算类
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#include <iostream>
#include <cmath>
#include "../stack.h"


//==============================================================================
/*!
 * @brief OperatorCalc class
 *
 * 运算符计算类
 *
 */
//==============================================================================
class OperatorCalc
{
public:
    OperatorCalc (char _ch):m_ch(_ch){this->m_type = this->get_type();};

    int     get_type();

    bool    is_unary_op(){return this->m_type == 1 ? true : false;}
    bool    is_binary_op(){return this->m_type == 2 ? true : false;};
    //bool    is_ternary_op(){return this->m_type == 3 ? true : false;};

    float   calculate(float a);
    float   calculate(float a, float b);
    //float   calculate(float a, float b, float c);

protected:
    float   factorial(float a);

private:
    char m_ch;
    unsigned char m_type;
};



/** 所有支持的运算符 */
#define N_OP 9

extern const char table_optr_priority[N_OP][N_OP];
extern unsigned int get_optr_index(char ch);
extern char get_optr_priority(char ch1, char ch2);

