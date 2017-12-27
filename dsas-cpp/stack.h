//==============================================================================
/*!
 * @file stack.h
 * @brief 栈结构
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _STACK_H
#define _STACK_H

#include "vector.h"
#include "list.h"

namespace dsa
{

/*!
 * @addtogroup  LStack
 *
 * @{
 */

/*!
 * @brief 栈
 *
 * 使用Vector构造栈
 *
 */
template <typename T>
class Stack : public dsa::Vector<T>
{
public:
    Stack() {dsa::Vector<T>();}

    /** 入栈 */
    void    push(const T& e) {this->push_back(e);}
    /** 出栈 */
    T       pop() {return this->remove(this->size()-1);}
    /** 返回栈顶数据 */
    T       top() const {return this->m_array[this->size()-1];}
};


/*!
 * @brief 栈
 *
 * 使用List构造栈
 *
 */
template <typename T>
class StackList : public dsa::List<T>
{
public:
    StackList() {dsa::List<T>();}

    /** 入栈 */
    void    push(const T& e) {this->push_back(e);}
    /** 出栈 */
    T       pop() {return this->remove(this->back());}
    /** 返回栈顶数据 */
    T       top() const {return this->back()->data;}
};

/*! @} */
    
} /* dsa */

#endif /* ifndef _STACK_H */
