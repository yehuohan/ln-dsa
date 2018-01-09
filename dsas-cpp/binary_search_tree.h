//==============================================================================
/*!
 * @file binary_search_tree.h
 * @brief 二叉搜索树(BST)
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

#include "binary_tree.h"
#include "share/swap.h"
#include "share/compare.h"

namespace dsa
{

/*!
 * @addtogroup TBinarySearchTree
 * @{
 */


/*!
 * @brief 二叉搜索树类模板
 *
 * <pre>
 * 节点数: n
 * 树高度: h，最坏情况下为n
 * search, insert, remove在最坏情况下需要O(h)时间。
 * </pre>
 */
template <typename T>
class BinSearchTree : public BinTree<T>
{
public:
    virtual BinNodePtr<T>&  search(const T&);
    virtual BinNodePtr<T>   insert(const T&);
    virtual bool            remove(const T&);

protected:
    BinNodePtr<T>     m_hot;
    BinNodePtr<T>     connect34(
            BinNodePtr<T>, BinNodePtr<T>, BinNodePtr<T>,
            BinNodePtr<T>, BinNodePtr<T>, BinNodePtr<T>, BinNodePtr<T>);
    BinNodePtr<T>     rotate_at(BinNodePtr<T>);
};

/*! @} */


/*!
 * @brief 递归实现查找。
 *
 * @param node: 从根结点node开始查找。
 * @param e: 查找目标。
 * @param hot: 指向命中节点的父节点。hot为nullptr的两中情况：树中没有一个节点，或者查找的node正好是root节点
 * @return 返回命中节点，命中节点可能为nullptr(即未查找到目标)，也可能为目标节点。
 * @retval None
 */
template <typename T>
static BinNodePtr<T>& search_in(
        BinNodePtr<T>& node,
        const T& e,
        BinNodePtr<T>& hot)
{
    if (!node || dsa::is_equal(e, node->data))
        return node;
    hot = node;
    return search_in(dsa::less_than(e, node->data) ? node->left : node->right, e, hot);
                            // 递归传入search_in的node是hot的子节点
}

/*!
 * @brief 查找接口。
 *
 * @param e: 查找目标。
 * @return
 * @retval None
 */
template <typename T>
BinNodePtr<T>& BinSearchTree<T>::search(const T& e)
{
    return search_in(this->m_root, e, this->m_hot = nullptr);
}

/*!
 * @brief 插入节点
 *
 * @param e: 插入目标。
 * @return
 * @retval None
 */
template <typename T>
BinNodePtr<T> BinSearchTree<T>::insert(const T& e)
{
    BinNodePtr<T>& node = this->search(e);
    if (!node)      // 禁止相同元素
    {
        node = new BinNode<T>(e, this->m_hot);      // node一定是m_hot的子节点，见search代码
        this->m_size++;
        this->update_height_above(node);
    }
    return node;
}

/*!
 * @brief 删除节点
 *
 * <pre>
 *
 * 单分支删除d节点：
 *   a                a
 *  / \              / \
 * T0  b            T0  b
 *    / \     =>       / \
 *   T1  d            T1  c (d)
 *      /
 *     c
 *
 * 双分支删除d节点：
 *    d                  c
 *  /   \              /   \
 * T0    b            T0    b
 *     /   \     =>       /   \
 *    c     T1           d     T1
 *     \   / \            \   / \
 *      a T2 T3            a T2 T3
 * 节点c为节点d直接后继，交换c和d，然后按单分支情况删除d
 *
 * </pre>
 *
 * @param node: 待删除的目标节点
 * @param hot: 目标节点的父节点
 * @return 返回被删除节点位置的新节点，hot为返回节点的父节点
 * @retval None
 */
template <typename T>
static BinNodePtr<T> remove_at(
        BinNodePtr<T>& node,
        BinNodePtr<T>& hot)
{
    BinNodePtr<T> w = node;
    BinNodePtr<T> succ = nullptr;
    // 只有右子树(或左右子树均没有，则返回nullptr，即被删除节点位置没有新节点)
    if(!node->left) succ = node = node->right;
    // 只有左子树
    else if(!node->right) succ = node = node->left;
    // 左右分支均存在
    else
    {
        // 右子树存在，故node的直接后继w为node右子树最靠左（最小）的节点
        w = w->successor();
        // 交换直接后继w与目标节点的数据，交换完后，w成为待删除的目标节点
        dsa::swap(w->data, node->data);
        BinNodePtr<T> u = w->parent;
        // 后继节点w只可能有右子树，不可能有左子树
        if (u == node)
        {
            // 后继节点w即为node的右子节点
            u->right = succ = w->right;
        }
        else
        {
            u->left = succ = w->right;
        }
    }

    hot = w->parent;                // 待删除节点的父节点
    // succ不为nullptr，则hot为succ的父节点
    // succ为nullptr，则hot的子节点w被删除后，也为nullptr
    if (succ) succ->parent = hot;   // 设置接替节点的父节点
    delete w;                       // 删除节点

    return succ;
}

/*!
 * @brief 删除节点。
 *
 * @param e: 删除目标。
 * @return
 * @retval None
 */
template <typename T>
bool BinSearchTree<T>::remove(const T& e)
{
    BinNodePtr<T>& node = this->search(e);
    if (!node) return false;
    remove_at(node, m_hot);
    this->m_size--;
    this->update_height_above(m_hot);
    return true;
}


/*!
 * @brief 树结点联接
 *
 * <pre>
 * 最终的树如下所示：
 *       b
 *     /   \
 *    a     c
 *   / \   / \
 *  T0 T1 T2 T3
 *
 * </pre>
 *
 * @param a,b,c,T0,T1,T2,T3: 待连接的节点
 * @return 子树的根节点
 * @retval None
 */
template <typename T>
BinNodePtr<T> BinSearchTree<T>::connect34(
        BinNodePtr<T> a, BinNodePtr<T> b, BinNodePtr<T> c,
        BinNodePtr<T> T0, BinNodePtr<T> T1, BinNodePtr<T> T2, BinNodePtr<T> T3)
{
    a->left = T0;
    a->right = T1;
    if (T0) T0->parent = a;
    if (T1) T1->parent = a;
    this->update_height(a);

    c->left = T2;
    c->right = T3;
    if (T2) T2->parent = c;
    if (T3) T3->parent = c;
    this->update_height(c);

    b->left = a;  a->parent = b;
    b->right = c; c->parent = b;
    this->update_height(b);

    return b;
}

/*!
 * @brief 节点旋转调整
 *
 * <pre>
 * 示意图如下(包括对称情况)：
 * zag(旋转gp)                       | zig(旋转gp)
 * 单旋:                             |  单旋:
 *   g                       p       |      g                       p
 * /   \                   /   \     |    /   \                   /   \
 * T0  p        =>        g     v    |    p   T3       =>        v     g
 *    / \                / \   / \   |   / \                    / \   / \
 *   T1 v               T0 T1 T2 T3  |   v T2                  T0 T1 T2 T3
 *     / \                           |  / \
 *    T2 T3                          | T0 T1
 *                                   |
 * zag-zig(先zig旋转pv，再zag旋转gv) | zig-zag(先zag旋转pv，再zig旋转gv)
 * 双旋:                             |  双旋:
 *   g                       v       |      g                       v
 * /   \                   /   \     |    /   \                   /   \
 * T0   p                 g     p    |   p    T3                 p     g
 *    /   \              / \   / \   | /   \                    / \   / \
 *   v    T3    =>      T0 T1 T2 T3  | T0   v          =>      T0 T1 T2 T3
 *  / \                              |     / \
 * T1 T2                             |    T1 T2
 *                                   |
 * </pre>
 *
 * @param v: 调整的节点(子树(如图)中高度最低的节点)
 * @return 子树的根节点
 * @retval None
 */
template <typename T>
BinNodePtr<T> BinSearchTree<T>::rotate_at(BinNodePtr<T> v)
{
    BinNodePtr<T> p = v->parent;
    BinNodePtr<T> g = p->parent;
    if (BN_IsLeftChild(*p))
    {
        if (BN_IsLeftChild(*v))
        {
            // zig 单旋
            p->parent = g->parent;      // 设置子树根节点的父节点
            return this->connect34(v, p, g,
                    v->left, v->right, p->right, g->right);
        }
        else
        {
            // zig-zag 双旋
            v->parent = g->parent;      // 设置子树根节点的父节点
            return this->connect34(p, v, g,
                    p->left, v->left, v->right, g->right);
        }
    }
    else if (BN_IsRightChild(*p))
    {
        if (BN_IsLeftChild(*v))
        {
            // zag-zig 双旋
            v->parent = g->parent;      // 设置子树根节点的父节点
            return this->connect34(g, v, p,
                    g->left, v->left, v->right, p->right);
        }
        else
        {
            // zag 单旋
            p->parent = g->parent;      // 设置子树根节点的父节点
            return this->connect34(g, p, v,
                    g->left, p->left, v->left, v->right);
        }
    }
}

} /* dsa */

#endif /* ifndef _BINARY_SEARCH_TREE_H */

