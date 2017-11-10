
//==============================================================================
/*!
 * @file queue.h
 * @brief Queue struct
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
 * @brief Queue class
 *
 * inheriting from list
 * taking list-head and queue-front and list-tail as queue-rear
 *
 */
//==============================================================================
template <typename T>
class Queue : private dsa::List<T>
{
public:
    Queue(){dsa::List<T>();}

    bool    is_empty() const {return dsa::List<T>::is_empty();}
    unsigned int size() const {return dsa::List<T>::size();}

    // 尾进头出
    /** return the front element */
    T       front() const {return (dsa::List<T>::first())->data;};
    /** pop the element from front */
    //T       pop_front() {return dsa::List<T>::remove(dsa::List<T>::first());}
    T       dequeue() {return dsa::List<T>::remove(dsa::List<T>::first());}

    /** return the rear element */
    T       rear() const {return dsa::List<T>::last()->data;}
    /** push the element to the rear */
    //void    push_rear(const T& ele) { dsa::List<T>::push_back(ele);}
    void    enqueue(const T& ele) { dsa::List<T>::push_back(ele);}
};

/*! @} */

}


#endif /* ifndef _QUEUE_H */
