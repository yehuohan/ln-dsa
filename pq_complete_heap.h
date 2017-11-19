
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
 * @name 堆节点相关操作
 * @{
 */
#define PQ_InHeap(n,i)      ((0 <= (i)) && ((i) < (n))) /**< 判断是否在二叉堆中 */
#define PQ_ParentValid(i)   ((i) > 0)           /**< 判断i是否有父节点 */
#define PQ_Parent(i)        (((i)-1) >> 1)      /**< i的父节点（floor((i-1)/2)，i无论正负） */
#define PQ_LeftChild(i)     (1 + ((i) << 1))    /**< i的左孩子，即 (2*i+1) */
#define PQ_RightChild(i)    ((1 + (i)) << 1)    /**< i的右孩子，即 (2*i+2) */
#define PQ_LeftChildValid(n, i)     PQ_InHeap(n, PQ_LeftChild(i))  /**< 判断i是否有一个（左）孩子 */
#define PQ_RightChildValid(n, i)    PQ_InHeap(n, PQ_RightChild(i)) /**< 判断i是否有两个孩子，对于完全二叉堆，有右孩子，必有左孩子*/

/*! @} */


/*!
 * @brief 完全二叉堆模板类
 *
 * 优先级队列只需要最快的找到最大值，而不需要维护所有元素间的顺序；
 * 如图所示：只需要保证完全二叉堆的根是最大值，其余只要保证堆序性；
 * 完全二叉堆的节点数为n，则树高度h，可控制在O(log(n))。
 *
 * 堆序性：H[i] <= H[parent(i)]
 *
 *          15 
 *       /      \
 *      13      10
 *    /   \   /   \
 *   7    5  6    9
 *  / \  /
 * 2  0 3
 *
 * 向量存储： 15, 13,10, 7,5,6,9, 2,0,3
 * 向量下标： 0 ,  1, 2, 3,4,5,6, 7,8,9
 *
 * 对于完全二叉堆的满元素层，第i+1层的节点数是第i层的两倍，
 * 这是二叉堆实现索引父节点、子节点等计算的原理。
 *
 */
template <typename T>
class PqComplHeap : public PQ<T>, public Vector<T>
{
protected:
    int percolate_up(int i);
    int percolate_down(int n, int i);
    void heapify(int n);

public:
    PqComplHeap() {}
    PqComplHeap(const T* A, int n) : PQ<T>(), Vector<T>()
    {
        this->copy_from(A, 0, n);
        this->heapify(n);
    }

    void insert(const T&);

    /*!
     * @brief 获取最大值，即优先级最高的元素
     *
     * @param None
     * @return
     * @retval None
     */
    T get_max() {return this->m_ar[0];};
    T del_max();

private:
    int proper_parent(int n, int i);
};

/*! @} */


/*!
 * @brief 获取父子三者的最大者
 *
 * 获取父节点与其子节点间的最大者
 *
 * @param n: 二叉堆元素数量
 * @param i: 父节点下标
 * @return 返回最大者的下标
 * @retval None
 */
template <typename T>
int PqComplHeap<T>::proper_parent(int n, int i)
{
#define PQ_Bigger(i, j)     (((this->m_ar[i]) >= (this->m_ar[j])) ? (i) : (j))
    if (PQ_RightChildValid(n, i))
    {
        // i的左右孩子均存在
        return PQ_Bigger(i, PQ_Bigger(PQ_LeftChild(i), PQ_RightChild(i)) );
    }
    else if(PQ_LeftChildValid(n, i))
    {
        // 只有i的左孩子存在
        return PQ_Bigger(i, PQ_LeftChild(i));
    }
    else
        return i;
#undef PQ_Bigger
}

/*!
 * @brief 上滤
 *
 * @param i: 新插入元素的下标
 * @return 返回新插入元素的下标
 * @retval None
 */
template <typename T>
int PqComplHeap<T>::percolate_up(int i)
{
    T ele = this->m_ar[i];
    while(PQ_ParentValid(i))
    {
        int j = PQ_Parent(i);
        if (ele < this->m_ar[j])
            break;
        // 新插入元素比父元素大，则上滤元素
        this->m_ar[i] = this->m_ar[j];
        i = j;
    }
    // 将新插入元素，放到最终的节点位置
    this->m_ar[i] = ele;
    return i;
}

/*!
 * @brief 下滤
 *
 * 对前n个元素的第i个元素进行下滤
 *
 * @param n: 元素数量
 * @param i: 进行下滤的元素下标
 * @return
 * @retval None
 */
template <typename T>
int PqComplHeap<T>::percolate_down(int n, int i)
{
    int j;
    while(i!= (j = this->proper_parent(n, i)))
    {
        // i的子节点元比i大，则下滤
        T tmp = this->m_ar[i];
        this->m_ar[i] = this->m_ar[j];
        this->m_ar[j] = tmp;
        i = j;
    }
    return i;
}

/*!
 * @brief 插入元素
 *
 * @param e: 待插入的元素
 * @return
 * @retval None
 */
template <typename T>
void PqComplHeap<T>::insert(const T& e)
{
    // 使用Vector的insert函数
    Vector<T>::push_back(e);
    // 对新插入的e进行上滤检测
    this->percolate_up(this->m_size - 1);
}

/*!
 * @brief 删除最大值元素，最优先级最高的元素
 *
 * @param None
 * @return
 * @retval None
 */
template <typename T>
T PqComplHeap<T>::del_max()
{
    T max_elem = this->m_ar[0];
    this->m_ar[0] = this->m_ar[--this->m_size];
    this->percolate_down(this->m_size, 0);
    return max_elem;
}


} /* dsa */ 

#endif /* ifndef _PQ_COMPLETE_HEAP_H */

