
//==============================================================================
/*!
 * @file pq_complete_heap.h
 * @brief 完全二叉堆模版类
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _PQ_COMPLETE_HEAP_H
#define _PQ_COMPLETE_HEAP_H

#include "vector.h"
#include "priority_queue.h"

namespace dsa
{

/*!
 * @addtogroup LPQ
 *
 * @{
 */


/*!
 * @brief 完全二叉堆模板类
 *
 * 堆序性：H[i] <= H[parent(i)]
 *
 */
template <typename T>
class PqComplHeap : public PQ<T>, public Vector<T>
{
protected:
    int percolate_up(int n, int i);
    int percolate_down(int i);
    void heapify(int n);

public:
    PqComplHeap(const T* A, int n)
    {
        this->copy_from(A, 0, n);
        this->heapify(n);
    }

    void insert(const T&);
    T get_max() {return this->m_ar[0];};
    T del_max();
};

/*! @} */



} /* dsa */ 

#endif /* ifndef _PQ_COMPLETE_HEAP_H */

