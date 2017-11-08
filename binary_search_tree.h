
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

namespace dsa
{

/*!
 * @addtogroup Tree
 * @{
 */


/*!
 * @brief 词条类，实现元素的比较
 *
 */
template <typename K, typename V> struct Entry
{
    K key;
    V value;

    Entry(K _key = K(), V _value = V()) : key(_key), value(_value) {}
    Entry(const Entry<K,V>& e): key(e.key), value(e.value) {}

    bool operator< (const Entry<K,V>& e) const {return key < e.key;}
    bool operator> (const Entry<K,V>& e) const {return key > e.key;}
    bool operator== (const Entry<K,V>& e) const {return key == e.key;}
    bool operator!= (const Entry<K,V>& e) const {return key != e.key;}
};

/*!
 * @brief 二叉搜索树类模板
 *
 */
template <typename T>
class BinSearchTree : public BinTree<T>
{
public:
    virtual BinNode<T>*&    search(const T&);
    virtual BinNode<T>*     insert(const T&);
    virtual bool            remove(const T&);

protected:
    BinNode<T>*     m_hot;
    BinNode<T>*     connect34(
            BinNode<T>*, BinNode<T>*, BinNode<T>*,
            BinNode<T>*, BinNode<T>*, BinNode<T>*, BinNode<T>*);
    BinNode<T>*     rotate_at(BinNode<T>*);
};


/*!
 * @brief 递归实现查找。
 *
 * @param node: 从根结点node开始查找。
 * @param e: 查找目标。
 * @param hot: 指向命中节点的父节点。
 * @return 返回命中节点，命中节点可能为nullptr，也可能为目标节点。
 * @retval None
 */
template <typename T>
static BinNode<T>*& search_in(
        BinNode<T>*& node,
        const T& e,
        BinNode<T>*& hot)
{
    if (!node || e == node->data)
        return node;
    hot = node;
    return search_in((e < node->data) ? node->left : node->right, e, hot);
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
BinNode<T>*& BinSearchTree<T>::search(const T& e)
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
BinNode<T>* BinSearchTree<T>::insert(const T& e)
{
    BinNode<T>*& node = this->search(e);
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
 *   T1  c            T1  d (c)
 *      /
 *     d
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
 * @return
 * @retval None
 */
template <typename T>
static BinNode<T>* remove_at(
        BinNode<T>*& node,
        BinNode<T>*& hot)
{
    BinNode<T>* w = node;
    BinNode<T>* succ = nullptr;
    // 只有右子树
    if(!node->left) succ = node = node->right;
    // 只有左子树
    else if(!node->right) succ = node = node->left;
    // 左右分支均存在
    else
    {
        // 右子树存在，故node的直接后继w为node右子树最靠左（最小）的节点
        w = w->successor();
        // 交换直接后继w与目标节点的数据，交换完后，w成为待删除的目标节点
        T tmp = w->data;
        w->data = node->data;
        node->data = tmp;
        BinNode<T>* u = w->parent;
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
    BinNode<T>*& node = this->search(e);
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
 * @param None
 * @return 子树的根节点
 * @retval None
 */
template <typename T>
BinNode<T>* BinSearchTree<T>::connect34(
        BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
        BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3)
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
 * zag-zag(先旋转pv，再旋转gv)       | zig-zig(先旋转pv，再旋转gv)
 * 单旋:                             |  单旋:
 *   g                       p       |      g                       p
 * /   \                   /   \     |    /   \                   /   \
 * T0  p        =>        g     v    |    p   T3       =>        v     g
 *    / \                / \   / \   |   / \                    / \   / \
 *   T1 v               T0 T1 T2 T3  |   v T2                  T0 T1 T2 T3
 *     / \                           |  / \
 *    T2 T3                          | T0 T1
 *                                   |
 * zag-zig(先旋转pv，再旋转gv)       | zig-zag(先旋转pv，再旋转gv)
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
 * @param v 调整的节点(子树(如图)中高度最低的节点)
 * @return 子树的根节点
 * @retval None
 */
template <typename T>
BinNode<T>* BinSearchTree<T>::rotate_at(BinNode<T>* v)
{
    BinNode<T>* p = v->parent;
    BinNode<T>* g = p->parent;
    if (BN_IsLeftChild(*p))
    {
        if (BN_IsLeftChild(*v))
        {
            // zig-zig 单旋
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
            // zag-zag 单旋
            p->parent = g->parent;      // 设置子树根节点的父节点
            return this->connect34(g, p, v,
                    g->left, p->left, v->left, v->right);
        }
    }
}


/*! @} */

// namespace dsa end
}

#endif /* ifndef _BINARY_SEARCH_TREE_H */

