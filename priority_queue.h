
//==============================================================================
/*!
 * @file priority_queue.h
 * @brief 优先级队列接口抽象类
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _PRIORITY_QUEUE_H
#define _PRIORITY_QUEUE_H

namespace dsa
{

/*!
 * @brief 优先级队列接口抽象类
 *
 */
template <typename T>
class PQ
{
public:
    virtual void insert(const T&) = 0;
    virtual T get_max() = 0;
    virtual T del_max() = 0;
};
    
} /* dsa */ 

#endif /* ifndef _PRIORITY_QUEUE_H */
