
//==============================================================================
/*!
 * @file queue.h
 * @brief queue struct 
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================


#ifndef _QUEUE_H
#define _QUEUE_H value

#include "list.h"
#include "vector.h"

namespace dsa
{

/*!
 * @addtogroup Linear
 * 
 * @{
 */

//==============================================================================
/*!
 * @brief queue class 
 *
 * inheriting from list 
 * taking list-head and queue-front and list-tail as queue-rear 
 *
 */
//==============================================================================
template <typename T>
class queue : private dsa::list<T>
{
public:
    queue(){dsa::list<T>();}

    bool    is_empty() const {return dsa::list<T>::is_empty();}
    unsigned int size() const {return dsa::list<T>::size();}

    // 尾进头出
    /** return the front element */
    T       front() const {return (dsa::list<T>::first())->data;};
    /** pop the element from front */
    T       pop_front() {return dsa::list<T>::remove(dsa::list<T>::first());}

    /** return the rear element */
    T       rear() const {return dsa::list<T>::last()->data;}
    /** push the element to the rear */
    void    push_rear(const T& ele) { dsa::list<T>::push_back(ele);}
};

/*! @} */

}


#endif /* ifndef _QUEUE_H */
