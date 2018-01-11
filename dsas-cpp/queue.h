
//==============================================================================
/*!
 * @file queue.h
 * @brief 队列结构
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

namespace dsa
{

/*!
 * @addtogroup LQueue
 *
 * @{
 */

/*!
 * @brief 队列类
 *
 * 使用列表构造队列，实现尾进头出
 *
 */
template <typename T>
class Queue : public dsa::List<T>
{
public:
    Queue(){dsa::List<T>();}

    /** 返回头部元素 */
    T       front() const {return (dsa::List<T>::front())->data;};
    /** 头部元素出队 */
    T       dequeue() {return dsa::List<T>::remove(dsa::List<T>::front());}

    /** 返回尾部元素 */
    T       rear() const {return dsa::List<T>::back()->data;}
    /** 尾部元素入队 */
    void    enqueue(const T& ele) { dsa::List<T>::push_back(ele);}
};


/*!
 * @brief 数组循环队列
 *
 * 使用数组构造队列，实现尾进头出
 */
template <typename T>
class ArrayQueue
{
protected:
    int     m_cap;          /**< 队列容量 */
    int     m_head;         /**< 头部下标 */
    int     m_tail;         /**< 尾部下标 */
    T*      m_array;

public:
    ArrayQueue(int cap) : m_cap(cap), m_head(0), m_tail(-1) {this->m_array = new T[cap];};
    ~ArrayQueue() {delete[] this->m_array;};

    /** 返回元素数量 */
    int     size() {return (this->m_tail - this->m_head + 1);}
    /** 判断是否为空 */
    bool    is_empty() {return (this->m_tail < this->m_head);}
    /** 判断是否为满 */
    bool    is_full() {return (this->size() == m_cap);}

    /** 返回头部元素，自行判断是否为空 */
    T       front()
    {return this->m_array[this->m_head % this->m_cap];}
    /** 头部元素出队，自行判断是否为空 */
    T       dequeue()
    {return this->m_array[(this->m_head++) % this->m_cap];}

    /** 返回尾部元素，自行判断是否为空 */
    T       rear()
    {return this->m_array[this->m_tail % this->m_cap];}
    /** 尾部元素入队，自行判断是否为满 */
    void    enqueue(const T& ele)
    {this->m_array[(++this->m_tail) % this->m_cap] = ele;}
};

/*! @} */

} /* dsa */

#endif /* ifndef _QUEUE_H */
