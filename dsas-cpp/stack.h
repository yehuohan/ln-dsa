
//==============================================================================
/*!
 * @file stack.h
 * @brief Stack struct
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _STACK_H
#define _STACK_H

#include "list.h"
#include "vector.h"

namespace dsa
{

/*!
 * @addtogroup  LStack
 *
 * @{
 */

/*!
 * @brief Stack class
 *
 * inheriting from vector and take vector-end as stack-top
 *
 */
template <typename T>
class Stack : protected dsa::Vector<T>
{
public:
    Stack() {dsa::Vector<T>();}

    bool            is_empty() const {return dsa::Vector<T>::is_empty();}
    unsigned int    size() const {return dsa::Vector<T>::size();}
    void            clear(){dsa::Vector<T>::clear();}

    /** push data to stack */
    void            push(const T& e) {this->push_back(e);}
    /** pop data from statck */
    T               pop() {return this->remove(this->size()-1);}
    /** return top-data */
    T               top() const {return this->m_array[this->size()-1];}
};


template <typename T>
class StackList : private dsa::List<T>
{
public:
    StackList() {List<T>::List();}
};

/*! @} */


// namespace dsa end
}

#endif /* ifndef _STACK_H */
