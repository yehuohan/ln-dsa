//==============================================================================
/*!
 * @file binary_tree.h
 * @brief 二叉树的基本模块类
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "vector.h"
#include "binary_node.h"

namespace dsa
{

/*!
 * @addtogroup TBinaryTree
 * @{
 */

/*!
 * @brief 二叉树类
 *
 * <pre>
 * (1) 基本概念
 * ----------------- r      ------
 *                  /
 *                 .
 * depth(v)        .
 *                 .
 *                 *
 *                / \
 * ----------    v  ...      height(r)
 *              / \
 * height(v)   .
 *             .
 * ----------  .
 *            / \
 *              .
 *              .
 *              .           ------
 *
 * v的深度：depth(v)，指子树根节点v的深度
 * 根节点深度为0
 *
 * v的高度：height(v)，指子树根节点v的高度
 * 空树高度取为-1
 *
 * 叶子节点：没有后代(子节点)的节点
 *
 * (2) 二叉树：节点度数<=2的树
 * 对于深度为k的节点，数量至多为2^k个；
 *
 * 含n个节点，高度为h的二叉树： h < n < 2^(h+1)
 * n = h+1时，树成为单链
 * n = 2^(h+1)-1时，二叉树为满树
 *
 * </pre>
 */
template <typename T>
class BinTree
{
protected:
    int             m_size;     /**< 节点数量 */
    BinNodePtr<T>   m_root;     /**< 树根节点 */

protected:
    virtual int update_height(BinNodePtr<T> node);
    void        update_height_above(BinNodePtr<T> node);

public:
    BinTree() : m_size(0), m_root(nullptr) {}
    BinTree(const T& ele) : m_size(1) {this->m_root = new BinNode<T>(ele, nullptr);}
    ~BinTree() {if (m_root) this->remove(m_root);}

    int     size() const {return this->m_size;}
    bool    is_empty() const {return !this->m_root;}
    int     remove(BinNodePtr<T>);

    /** 返回根节点 */
    BinNodePtr<T> root() {return this->m_root;}
    /** 插入根节点 */
    BinNodePtr<T> insert_root(const T& ele) {return this->m_root = new BinNode<T>(ele, nullptr);}
    BinNodePtr<T> insert_left(BinNodePtr<T> node, const T& ele);
    BinNodePtr<T> insert_right(BinNodePtr<T> node, const T& ele);
};

template <typename T> static int remove_at(BinNodePtr<T> node);
template <typename T> static void construct_bintree_pre_in(const dsa::Vector<T>& pre, const dsa::Vector<T>& in, BinNodePtr<T>& node);
template <typename T> void construct_bintree(const dsa::Vector<T>& pre, const dsa::Vector<T>& in, BinTree<T>& bt);

/*! @} */


/*!
 * @brief 更新node高度
 *
 * @param node: BinNode节点
 * @return 返回节点高度
 * @retval None
 */
template <typename T>
int BinTree<T>::update_height(BinNodePtr<T> node)
{
    // 叶子结点没有子结点了，其高度为 1 + (-1) = 0
    int a = node->left ? node->left->height : -1;
    int b = node->right ? node->right->height : -1;
    return node->height = 1 + ((a>=b)?a:b);
}

/*!
 * @brief 更新node及祖先高度
 *
 * @param node: BinNode节点
 * @return
 * @retval None
 */
template <typename T>
void BinTree<T>::update_height_above(BinNodePtr<T> node)
{
    while(node)
    {
        update_height(node);
        node = node->parent;
    }
}

/*!
 * @brief 删除以位置node处节点为根的子树
 *
 * @param node: 待删除节点
 * @return 返回删除的节点总数
 * @retval None
 */
template <typename T>
static int remove_at(BinNodePtr<T> node)
{
    if (!node) return 0;
    int n = 1 + remove_at(node->left) + remove_at(node->right);
    delete node;
    return n;

}

/*!
 * @brief 删除以位置node处节点为根的子树
 *
 * @param node: 子树根节点
 * @return 返回该子树原先的规模
 * @retval None
 */
template <typename T>
int BinTree<T>::remove(BinNodePtr<T> node)
{
    BinNodePtr<T> p = node->parent;
    if (p)
    {
        if (p->left == node) p->left = nullptr;
        else p->right = nullptr;
    }
    this->update_height_above(p);
    int n = remove_at(node);
    this->m_size -= n;
    return n;
}

/*!
 * @brief 插入左子结点
 *
 * @param node: 新结点的交结点
 * @param ele: 新结点中的数据
 * @return 返回新结点的指针
 * @retval None
 */
template <typename T>
BinNodePtr<T> BinTree<T>::insert_left(BinNodePtr<T> node, const T& ele)
{
    this->m_size ++;
    node->insert_left(ele);
    this->update_height_above(node);    // 新加结点后，高度变化
    return node->left;
}

/*!
 * @brief 插入右子结点
 *
 * @param node: 新结点的交结点
 * @param ele: 新结点中的数据
 * @return 返回新结点的指针
 * @retval None
 */
template <typename T>
BinNodePtr<T> BinTree<T>::insert_right(BinNodePtr<T> node, const T& ele)
{
    this->m_size ++;
    node->insert_right(ele);
    this->update_height_above(node);
    return node->right;
}


/*!
 * @brief 根据先序与中序序列重构二叉树的子树
 *
 * @param pre: 先序遍历序列
 * @param in: 中序遍历序列
 * @param node: 二叉树子树节点
 * @return
 * @retval None
 */
template <typename T>
static void construct_bintree_pre_in(
        const dsa::Vector<T>& pre,
        const dsa::Vector<T>& in,
        BinNodePtr<T>& node)
{
    // 查找子树的根节点
    int d_index = in.find(pre[0], 0, in.size());
    dsa::Vector<T> l_pre, l_in;        // 左子树先序与中序序列
    dsa::Vector<T> r_pre, r_in;        // 右子树先序与中序序列

    // 转移子树的先序与中序，先序与中序长度一样
    for(int k = 0; k < d_index; k ++)
    {
        l_pre.push_back(pre[k+1]);    // 转移左子树先序
        l_in.push_back(in[k]);        // 转移左子树中序
    }
    for(int k = d_index+1; k < in.size(); k++)
    {
        r_pre.push_back(pre[k]);      // 转移右子树先序
        r_in.push_back(in[k]);        // 转移右子树中序
    }

    // 若子树为空，则不需要继续向下构建
    if(!l_pre.is_empty())
    {
        // 插件子树的根节点
        BinNodePtr<T> left = node->insert_left(l_pre[0]);
        // 继续重构左子树与右子树
        construct_bintree_pre_in(l_pre, l_in, left);
    }
    if(!r_pre.is_empty())
    {
        BinNodePtr<T> right = node->insert_right(r_pre[0]);
        construct_bintree_pre_in(r_pre, r_in, right);
    }
}

/*!
 * @brief 根据先序与中序序列重构二叉树
 *
 * 可以重构二叉树的条件：
 * (1).已知先序或后序 + 中序
 * (2).已知先序或后序 + 为真二叉树(节点有0或2个子节点，或节点出度为偶数)
 *
 * @param pre: 先序遍历序列
 * @param in: 中序遍历序列
 * @param bt: 二叉树
 * @return
 * @retval None
 */
template <typename T>
void construct_bintree(
        const dsa::Vector<T>& pre,
        const dsa::Vector<T>& in,
        BinTree<T>& bt)
{
    bt.insert_root(pre[0]);
    BinNodePtr<T> root = bt.root();
    construct_bintree_pre_in(pre, in, root);
}

} /* dsa */

#endif /* ifndef _BINARY_TREE_H */
