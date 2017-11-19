
//==============================================================================
/*!
 * @file avl_tree.h
 * @brief AVL平衡二叉树
 *
 * 平衡二叉树：Balance Binary Search Tree
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _AVL_TREE_H
#define _AVL_TREE_H

#include "binary_search_tree.h"

namespace dsa
{

/*!
 * @addtogroup Tree
 * @{
 */

/*!
 * @name
 * @{
 */

/** 理想平衡 */
#define Balanced(v)         (BN_Stature((v).left) == BN_Stature((v).right))
/** 平衡因子 */
#define AVL_BalFac(v)       (BN_Stature((v).left) - BN_Stature((v).right))
/** AVL平衡 */
#define AVL_Balanced(v)     ((-2 < AVL_BalFac(v)) && (AVL_BalFac(v) < 2))

/*!
 * @brief 获取左右子树中较高的节点，以便获取最低层的节点(如图中节点v)
 *
 * <pre>
 *
 * 插入T2或T3时，会引起g失衡
 * 删除T0时(没有T2和T3)，会引起g失衡
 *   g
 * /   \
 * T0  p
 *    / \
 *   T1 v
 *     / \
 *    T2 T3
 *
 * 插入T1或T2时，会引起g失衡
 * 删除T0时(没有T1和T2)，会引起g失衡
 *   g
 * /   \
 * T0   p
 *    /   \
 *   v    T3
 *  / \
 * T1 T2
 *
 * </pre>
 */
#define AVL_TallerChild(x) ( \
    BN_Stature((x)->left) > BN_Stature((x)->right) ? (x)->left : (      /*左高*/ \
        BN_Stature((x)->left) < BN_Stature((x)->right) ? (x)->right : ( /*右高*/ \
            BN_IsLeftChild(*(x)) ? (x)->left : (x)->right               /*等高：与x父节点同侧者（zIg-zIg或zAg-zAg）优先*/ \
    )))

/*! @} */


/*!
 * @brief Avl平衡二叉树类
 *
 * 继承自二叉搜索树(BST)，沿用BST的search函数；
 * 需要借助avl平衡因子，实现平衡；
 * search, insert, remove在最坏情况下需要O(logh)时间。
 *
 */
template <typename T>
class AvlTree : public BinSearchTree<T>
{
public:
    BinNode<T>*     insert(const T&);
    bool            remove(const T&);
};

/*!
 * @brief AVL平衡二叉树的插入操作
 *
 * 在插入元素后，如果二叉树失衡，则要恢复平AVL平衡
 *
 * @param e 待插入的元素
 * @return 返回新插入的节点
 * @retval None
 */
template <typename T>
BinNode<T>* AvlTree<T>::insert(const T& e)
{
    BinNode<T>*& x = this->search(e);
    if (x) return x;                        // 不插入重复节点

    x = new BinNode<T>(e, this->m_hot);     // 新插入的节点
    this->m_size ++;
    BinNode<T>* node = x;

    // 从新插入节点的父节点开始，向上遍历所有父节点，检查是否满足Avl平衡
    for(BinNode<T>* g = this->m_hot; g; g = g->parent)
    {
        if(!AVL_Balanced(*g))               // 所有失衡节点中的最低点
        {
            BinNode<T>*& sub_node = RefFromParent(*g);
                                            // 获取g在父节点的孩子节点指针
            sub_node = this->rotate_at(AVL_TallerChild(AVL_TallerChild(g)));
                                            // 将rotate_at返回子树的根节点添加到Avl树中
            break;
        }
        else
            this->update_height(g);
    }

    return node;
}

/*!
 * @brief 移除节点
 *
 * @param e: 待移除节点的内容
 * @return
 * @retval None
 */
template <typename T>
bool AvlTree<T>::remove(const T& e)
{
    BinNode<T>*& x = this->search(e);
    if (!x) return false;
    remove_at(x, this->m_hot);
    this->m_size--;

    for (BinNode<T>* g = this->m_hot; g; g = g->parent)
    {
        if (!AVL_Balanced(*g))
        {
            BinNode<T>*& sub_node = RefFromParent(*g);
            g = sub_node = this->rotate_at(AVL_TallerChild(AVL_TallerChild(g)));
        }
        this->update_height(g);
    }

    return true;
}

/*! @} */

// namespace dsa end
}

#endif /* ifndef _AVL_TREE_H */
