
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

/*! @} */

// namespace dsa end
}

#endif /* ifndef _BINARY_SEARCH_TREE_H */

