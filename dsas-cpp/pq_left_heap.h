//==============================================================================
/*!
 * @file pq_left_heap.h
 * @brief 左式堆模板类
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef DSAS_PQ_LEFT_HEAP
#define DSAS_PQ_LEFT_HEAP

#include "priority_queue.h"
#include "binary_tree.h"
#include "share/swap.h"

namespace dsa
{

/*!
 * @addtogroup LPQ
 *
 * @{
 */

/*!
 * @brief 左式堆模板类
 *
 * 左式堆设计目标：有效完成堆的合并
 *
 * 引入外部节点(external nodes)，则就是内部节点(external nodes)
 * NPL: Null Path Length
 * npl(NULL) = 0
 * npl(x)    = 1 + min(npl(x->left), npl(x->right))
 * 由min可得到以下结论：
 * npl(x) = x到外部节点的最近距离(NULL节点的npl，即为自身到自身的距离)
 * npl(x) = 以x为根的最大满子树的高度(这里的满子树包括外部节点)
 *
 * 左倾: 对于任何内部节点x，都有npl(x->left) >= npl(x->right)
 * 左倾堆(左式堆): 所有内部节点均左倾
 * 推论: 对于左式堆的任何内部节点x，都有npl(x) = 1 + npl(x->right)；
 *       左式堆的子堆，仍是左式堆；
 *
 * 右侧链rightChain(x): 从节点x出发，一直沿右分支前进，所确立的分支；
 * 右侧链长度为d的左式堆，至少包含2^d-1个内部节点、2^(d+1)-1个节点；
 * 右侧链长度 d <= O(log(n))；
 * 沿着右子链合并两个左式堆，其时间复杂度 <= O(log(n))；
 *
 */
template <typename T>
class PqLeftHeap : public PQ<T>, public BinTree<T>
{
public:
    void    insert(const T&);
    T       get_max(){return this->m_root->data;}
    T       del_max();

protected:
    BinNodePtr<T>   merge(BinNodePtr<T>, BinNodePtr<T>);
};

/*! @} */


/*!
 * @brief 合并左式堆
 *
 * <pre>
 * a和b为两个左式堆的根节点：
 *
 *   a      b
 *  / \    / \
 * al ar  bl br
 *
 * 将a的右子堆ar与b合并，合并之后的结果AR仍做为a的右子堆
 *    a
 *  /   \
 * al   AR
 *    ------------
 *    |      b   |
 *    | ar  / \  |
 *    |    bl br |
 *    -----------
 * 比较al与AR的npl值，通过互换，使 npl(a->left) >= npl(a->right)
 *
 * </pre>
 *
 * @param a,b: 待合并的两个左式堆
 * @return
 * @retval None
 */
template <typename T>
BinNodePtr<T> PqLeftHeap<T>::merge(BinNodePtr<T> a, BinNodePtr<T> b)
{
    if (!a) return b;
    if (!b) return a;

    // 确保a >= b，因为合并后，a做为根节点，必须为最大值
    if (a->data < b->data)
        dsa::swap(a, b);
    // 合并a的右子堆与b
    a->right = this->merge(a->right, b);      // 因为右侧链长度 d <= O(log(n))，故merge最多递归d次，即时间复杂度为O(log(n))
    a->right->parent = a;
    // 使a继续满足左倾性
    if (!a->left || a->left->npl < a->right->npl)
        dsa::swap(a->left, a->right);
    // 更新npl，若a->right=nullptr，则a距a->right的距离为1
    a->npl = a->right ? (a->right->npl + 1) : 1;

    return a;
}

/*!
 * @brief 插入节点
 *
 * 将新插入节点看成一个单节点左式堆，使用merge完成插入。
 *
 * @param e: 待插入的节点元素
 * @return
 * @retval None
 */
template <typename T>
void PqLeftHeap<T>::insert(const T& e)
{
    BinNodePtr<T> v = new BinNode<T>(e);
    this->m_root = this->merge(this->m_root, v);
    this->m_root->parent = nullptr;
    this->m_size++;
}

/*!
 * @brief 删除最大值节点
 *
 * 删除根节点后，使用merge完成原根节点左右孩子节点的合并。
 *
 * @param None
 * @return 返回原根节点数据
 * @retval None
 */
template <typename T>
T PqLeftHeap<T>::del_max()
{
    BinNodePtr<T> rl = this->m_root->left;
    BinNodePtr<T> rr = this->m_root->right;
    T e = this->m_root->data;
    delete this->m_root;
    this->m_size--;

    this->m_root = this->merge(rl, rr);
    if (this->m_root)
        this->m_root->parent = nullptr;
    return e;
}

} /* dsa */
#endif /* ifndef DSAS_PQ_LEFT_HEAP */

