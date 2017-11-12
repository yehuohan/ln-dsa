//==============================================================================
/*!
 * @file b_tree.h
 * @brief b-tree类
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _B_TREE_H
#define _B_TREE_H

#include "b_node.h"

namespace dsa
{

/*!
 * @addtogroup Tree
 * @{
 */

/*!
 * @brief b-tree类
 *
 * <pre>
 *
 * 对于叶节点(以5阶b-tree为例)：
 * key       [0]  [1]  [2]  [3]     -> 最低层叶节点
 * child  [0]  [1]  [2]  [3]  [4]   -> 叶节点的子节点为external nodes，
 *                                     即只是在vector(child)有一个BTNode指针，值为nullptr;
 *                                     也只有external nodes指向nullptr。
 *
 *           r                      ---
 *          / \                      |
 *         /   \     internal nodes  |
 *        /     \                    |
 *       /_______\   (__为叶节点)   ---
 *      |||||||||||  external nodes  |
 *                                  ---
 *
 * </pre>
 */
template <typename T>
class BTree
{
protected:
    int m_size;                     /**< 关键码总数 */
    int m_order;                    /**< 阶次，也即最多分支数为m_order，每个节点关键码最多m_order-1 */
    dsa::BTNode<T>* m_root;         /**< 根节点 */
    dsa::BTNode<T>* m_hot;          /**< search最后访问的非空节点位置 */

    void solve_overflow(BTNode<T>*);
    void solve_underflow(BTNode<T>*);

public:
    BTree(int order = 3) : m_size(0), m_order(order){ this->m_root = new BTNode<T>(); }
    //~BTree(){if (m_root) ;}
    BTNode<T>*  search(const T& e);
    bool        insert(const T& e);
    bool        remove(const T& e);
};


/*!
 * @brief 修复上溢
 *
 * <pre>
 * 取中位数分裂，s = ⌊m/2⌋ (即向下取整)，如下图所示：
 * *[k0]*[k1]*[k2]* ... *[k(m-1)]*
 *                   |
 *                   V
 * *[k0]*[k1]*k(s-1)] * [ks] * [k(s+1)]* ... *[k(m-1)]*
 * ------------------   ----   -----------------------
 * 作为ks左子节点   上移至父节点         作为ks右子节点
 * 因为s = ⌊m/2⌋，故新的左右子节点的分支数均会满足>=⌈m/2⌉
 *
 * 以4阶b-tree为例：
 * [3]将上移至父节点
 *     *[0]*[10]*             *[0]*[3]*[10]*
 *      /  \                     /     \
 *     r    \   s     =>        /       \
 *           \ /               /         \
 *  *[1]*[2]*[3]*[5]*     *[1]*[2]*    *[5]*
 *  -----------------     ---------    -----
 *     原node节点       分裂后的node   新节点rc
 *
 * s之后(即[3]之后的*和[])的关键码和分支节点将转移到rc中;
 * 只在在根节点上溢时，树高度才会增加;
 * 根节点上溢时，分裂出的新根节点，且新的根节点只有2个分支;
 * 根据分裂特性，可知非叶节点的子节点不可指向nullptr。
 *
 * </pre>
 *
 * @param node: 发一上溢的节点
 * @return
 * @retval None
 */
template <typename T>
void BTree<T>::solve_overflow(BTNode<T>* node)
{
    // 根据分支数判断是否上溢
    if (node->child.size() <= this->m_order)
        return;

    // 判断是否为根节点
    BTNode<T>* p = node->parent;
    if (!p)
    {
        this->m_root = p = new BTNode<T>(); // BTNode默认构造函数，在没关键码时有一个指向nullptr子节点
        p->child[0] = node;
        node->parent = p;
    }

    // 转移node中s之后关键码和分支节点，追加到新节点rc中
    // 即转移示意图中的 *[5]* 部分
    int s = this->m_order / 2;              // 确定上移的节点位置
    BTNode<T>* rc = new BTNode<T>();        // BTNode默认构造函数，在没关键码时有一个指向nullptr子节点
    rc->child.clear();                      // 清除第一个默认添加的nullptr子节点
    for (int k = s + 1; k < node->key.size(); k ++)
    {
        rc->key.push_back(node->key[k]);
        rc->child.push_back(node->child[k]);
    }
    rc->child.push_back(node->child[node->child.size()-1]); // 分支节点数比关键码数多1
    if (rc->child[0])                       // 非叶节点的子节点均在存(不为nullptr)
    {
        for (int k = 0; k < rc->child.size(); k ++)
            rc->child[k]->parent = rc;      // 更新父节点
    }
    node->key.remove(s+1, node->key.size());// 移除原节点node中的关键码和分支
    node->child.remove(s+1, node->child.size());

    // 上移目标关键码
    // 即上移示意图的中 [3] 
    int r = p->key.search(node->key[s]);    // 确定移至父节点的位置
    p->key.insert(r+1, node->key.remove(s));
    p->child.insert(r+2, rc);               // 连接节点，p->child[r+2]现在指向rc
    rc->parent = p;

    solve_overflow(p);
}

template <typename T>
void BTree<T>::solve_underflow(BTNode<T>* node)
{

}

/*!
 * @brief b-tree查找
 *
 * <pre>
 *               r      r+1
 *                \     /
 * key       [k]  [k]  [k]
 * child  [c]  [c]  [c]  [c]
 *                  /
 *                r+1
 * 若key.search(e)返加r，若key[r]！= e，则有key[r] <= e < k[r+1]
 * 故继续向child[r+1]继续查找
 * </pre>
 *
 * @param e: 查找目标
 * @return
 * @retval nullptr: 没有找到目标，因为是逐层查找，故最后m_hot一定指向一个叶节点。
 */
template <typename T>
BTNode<T>* BTree<T>::search(const T& e)
{
    BTNode<T>* node = this->m_root;
    this->m_hot = nullptr;
    while(node)
    {
        int r = node->key.search(e);        // 返回不大于查找目标的下标
        if (0 <= r && e == node->key[r]) return node;   // 找到目标
        this->m_hot = node;
        node = node->child[r+1];            // 原理请看函数说明中的迭代查找示意图
        // 无论是否找到目标，child[r+1]都为m_hot的子节点
    }
    return nullptr;
}

/*!
 * @brief 插入节点
 *
 * <pre>
 * m_hot插入新节点示意图
 *
 *               r      r+1(新插入关键码，作为m_hot的一部分)
 *                \     /
 * key       [k]  [k]  [k] ...
 * child  [c]  [c]  [c]  [c] ...
 *                  /     \
 *                r+1     r+2(新插入子节点，作为external node)
 * 注：这里r为vector.search返回的，可以为-1，即表示新节点将插入到第0个位置
 *
 * </pre>
 *
 * @param e: 待插入节点关键码
 * @return
 * @retval None
 */
template <typename T>
bool BTree<T>::insert(const T& e)
{
    BTNode<T>* node = this->search(e);
    if (node) return false;

    // 找到关键码e在m_hot插入的位置
    int r = this->m_hot->key.search(e);
    this->m_hot->key.insert(r+1, e);
    this->m_hot->child.insert(r+2, nullptr);
    this->m_size++;

    this->solve_overflow(this->m_hot);

    return true;
}

/*! @} */
} /* dsa */

#endif /* ifndef _B_TREE_H */
