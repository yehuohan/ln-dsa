//==============================================================================
/*!
 * @file pq_list.h
 * @brief 基于List的优先级队列
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _PQ_LIST_H
#define _PQ_LIST_H

#include "priority_queue.h"
#include "list.h"

namespace dsa
{

/*!
 * @addtogroup LPQ
 *
 * @{
 */

/*!
 * @brief 
 *
 * 使用List建立优先级队列。
 *
 * List的插入和删除都在O(1)完成，查找最大值在O(n)完成。
 * 可以使用List已有接口完成优先级队列。
 *
 */
template <typename T>
class PqList : public dsa::PQ<T>, public dsa::List<T>
{
public:
    PqList() : dsa::PQ<T>(), dsa::List<T>() {}
    /** 从向量构造优先级队列 */
    PqList(const T* A, int n) : dsa::PQ<T>(), dsa::List<T>() {while(n-- > 0) this->push_front(A[n]);}

    /** 使用List的push_back实现插入，时间复杂弃O(1) */
    void insert(const T& ele) {this->push_back(ele);}
    /** 使用List的select_max，时间复杂度O(n) */
    T get_max() {return this->select_max()->data;}
    /** 使用List的select_max，再remove，时间复杂度O(n)+O(1) */
    T del_max() {return this->remove(this->select_max());}
};
    
/*! @} */

} /* dsa */

#endif /* ifndef _PQ_LIST_H */
