
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
 * @addtogroup TAvlTree
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
 * <pre>
 * 继承自二叉搜索树(BST)，沿用BST的search函数；
 * 需要借助avl平衡因子，实现平衡；
 *
 * 节点数: n
 * 树高度: h，可控制为O(log(n))
 * search, insert, remove在最坏情况下需要O(log(n))时间。
 * </pre>
 */
template <typename T>
class AvlTree : public BinSearchTree<T>
{
public:
    BinNodePtr<T>   insert(const T&);
    bool            remove(const T&);
};

/*! @} */


/*!
 * @brief AVL平衡二叉树的插入操作
 *
 * <pre>
 *
 * 插入节点，引起树失衡的基本情况共4种：
 *        (1)     (2)          (3)       (4)
 *         g       g            g         g
 *        / \     / \          / \       / \
 *       p   t   t   p        p   t     t   p
 *      /             \        \           /
 *     v               v        v         v
 *    /               /        /         /
 *   i               i        i         i
 *
 * g,p,v,t四个节点原本可以达到AVL平衡，但插入节点i做为v的子节点后，就会引起节点g失衡；
 * （因为插入节点i，使得g的高度变化，从而引起g的平衡因子超范围，即引起g失衡）。
 *
 * 这里估且设定 g->parent 节点为 x；
 *
 * 回复平衡的方法，即将g,p,v三个基本节点调整到以下形状：
 *       (1)      (2)          (3)       (4)
 *        p        p            v         v
 *       / \      / \          / \       / \
 *      v   g    g   v        p   g     g   p
 *     /     \  /   /          \   \   / \
 *    i      t t   i            i   t t   i
 *
 * 需要注意的是：
 * 回复平衡后，g所在位置(即现在的p,v节点处)节点的高度也会同样回复；
 * 所以从 x 节点以上的所有祖先节点高度均不会变化，即全树回复平衡。
 *
 * </pre>
 *
 * @param e 待插入的元素
 * @return 返回新插入的节点
 * @retval None
 */
template <typename T>
BinNodePtr<T> AvlTree<T>::insert(const T& e)
{
    BinNodePtr<T>& x = this->search(e);
    if (x) return x;                        // 不插入重复节点

    x = new BinNode<T>(e, this->m_hot);     // 新插入的节点
    this->m_size ++;
    BinNodePtr<T> node = x;

    // 从新插入节点的父节点开始，向上遍历所有父节点，检查是否满足Avl平衡
    for(BinNodePtr<T> g = this->m_hot; g; g = g->parent)
    {
        if(!AVL_Balanced(*g))               // 所有失衡节点中的最低点
        {
            BinNodePtr<T>& sub_node = RefFromParent(*g);
                                            // 获取g在父节点的孩子节点指针
            sub_node = this->rotate_at(AVL_TallerChild(AVL_TallerChild(g)));
                                            // 将rotate_at返回子树的根节点添加到Avl树中
            break;                          // g回复平衡后，局部子树高度复原，故调整结束
        }
        else
            this->update_height(g);
    }

    return node;
}

/*!
 * @brief 移除节点
 *
 * <pre>
 *
 * 插入节点，引起树失衡的基本情况共4种：
 *        (1)     (2)          (3)       (4)
 *         g       g            g         g
 *        / \     / \          / \       / \
 *       p   t   t   p        p   t     t   p
 *      /             \        \           /
 *     v               v        v         v
 *
 * g,p,v,t四个节点原本可以达到AVL平衡，但删除节点t后，就会引起节点g失衡；
 * （因为删除节点t，使得g的高度变化，从而引起g的平衡因子超范围，即引起g失衡）。
 *
 * 这里估且设定 g->parent 节点为 x；
 *
 * 回复平衡的方法，即将g,p,v三个基本节点调整到以下形状：
 *       (1)      (2)          (3)       (4)
 *        p        p            v         v
 *       / \      / \          / \       / \
 *      v   g    g   v        p   g     g   p
 *
 * 需要注意的是：
 * 回复平衡后，g所在位置(即现在的p,v节点处)节点的高度可能再次发生变化，可能引起g->parent失衡；
 * 所以，需要自 x 节点开始，沿着 parent 方向，检测所有祖先节点是否发生失衡，直至树根节点root；
 *
 * </pre>
 *
 * @param e: 待移除节点的内容
 * @return
 * @retval None
 */
template <typename T>
bool AvlTree<T>::remove(const T& e)
{
    BinNodePtr<T>& x = this->search(e);
    if (!x) return false;
    remove_at(x, this->m_hot);
    this->m_size--;

    for (BinNodePtr<T> g = this->m_hot; g; g = g->parent)
    {
        if (!AVL_Balanced(*g))
        {
            BinNodePtr<T>& sub_node = RefFromParent(*g);
            g = sub_node = this->rotate_at(AVL_TallerChild(AVL_TallerChild(g)));
        }
        this->update_height(g);
    }

    return true;
}

} /* dsa */

#endif /* ifndef _AVL_TREE_H */
