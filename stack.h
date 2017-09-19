
//==============================================================================
/*!
 * @file stack.h
 * @brief stack struct
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
 * @addtogroup  Linear
 * 
 * @{
 */

//==============================================================================
/*!
 * @brief stack class 
 *
 * inheriting from vector and take vector-end as stack-top
 *
 */
//==============================================================================
template <typename T>
class stack : private dsa::vector<T>
{
public:
    stack() {dsa::vector<T>();}

    bool            is_empty() const {return dsa::vector<T>::is_empty();}
    unsigned int    size() const {return dsa::vector<T>::size();}
    void            clear(){dsa::vector<T>::clear();}

    /** push data to stack */
    void            push(const T& e) {this->push_back(e);}
    /** pop data from statck */
    T               pop() {return this->remove(this->size()-1);}
    /** return top-data */
    T               top() const {return (*this)[this->size()-1];}
};




template <typename T>
class stack_list : private dsa::list<T>
{
public:
    stack_list() {list<T>::list();}
};

/*! @} */


// namespace dsa end
}

#endif /* ifndef _STACK_H */
