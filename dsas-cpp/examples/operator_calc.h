//==============================================================================
/*!
 * @file operator_calc.h
 * @brief 运算符计算类
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef DSAS_OPERATOR_CALC_H
#define DSAS_OPERATOR_CALC_H

#include <cmath>
#include "../stack.h"

namespace dsa
{

/*!
 * @addtogroup Example
 *
 * @{
 */

/** 所有支持的运算符数量 */
#define N_OP 9

extern const char   optr_priority_table[N_OP][N_OP];
extern unsigned int optr_get_index(char ch);
extern char         optr_get_priority(char ch1, char ch2);


/*!
 * @brief OperatorCalc class
 *
 * 运算符计算类
 *
 */
class OperatorCalc
{
private:
    char    m_ch;
    int     m_type;

protected:
    float   factorial(float a);
    int     get_type();

public:
    OperatorCalc (char _ch) : m_ch(_ch) {this->m_type = this->get_type();}

    /** 判断一元运算符 */
    bool    is_unary_op(){return this->m_type == 1 ? true : false;}
    /** 判断二元运算符 */
    bool    is_binary_op(){return this->m_type == 2 ? true : false;};
    /** 判断三元运算符 */
    bool    is_ternary_op(){return this->m_type == 3 ? true : false;};

    float   calculate(float a);
    float   calculate(float a, float b);
    //float   calculate(float a, float b, float c);
};

/*! @} */

} /* dsa */
#endif /* ifndef DSAS_OPERATOR_CALC_H */
