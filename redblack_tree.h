//==============================================================================
/*!
 * @file redblack_tree.h
 * @brief 红黑树
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _REDBLACK_TREE_H
#define _REDBLACK_TREE_H

#include "binary_node.h"
#include "binary_search_tree.h"

namespace dsa
{

/*!
 * @addtogroup Tree
 *
 * @{
 */

/*!
 * @brief 红黑树类
 *
 *<pre>
 * 1.树根：必为黑
 * 2.外部节点(类似于b-tree中的external nodes，值为nullptr)：均为黑
 * 3.其余节点：若为红，则子节点只能为黑，即任何节点的父节点不可能为红
 * 4.外部节点到根节点：途中黑节点数相等
 *</pre>
 *
 */
template <typename T>
class RedBlackTree : public BinSearchTree<T>
{
public:
    BinNode<T>* insert(const T&);
    bool        remove(const T&);

protected:
    void        solve_double_red(BinNode<T>*);
    void        solve_double_black(BinNode<T>*);
    int         update_height(BinNode<T>*);
};


/*!
 * @brief 更新节点高度
 *
 * 红黑树的高度，只对黑节点计数
 *
 * @param x: 待更新高度的节点
 * @return
 * @retval None
 */
template <typename T>
int RedBlackTree<T>::update_height(BinNode<T>* x)
{
    x->height = (BN_Stature(x->left) > BN_Stature(x->right)) ?
                BN_Stature(x->left) : BN_Stature(x->right);
    if (BN_IsBlack(x))
        x->height++;
    return x->height;
}

/*!
 * @brief 修正“双红”问题
 *
 * <pre>
 * 双红问题分2种类型，以下分别画出。
 * 其中，x为新插入节点，带有R的节点为红，否则为黑。
 *
 * RR-1: p的兄弟节点为黑（即子树T3的根节点u为黑），共分4种情况，这里画出2种，另两种完全对称
 * 先使用单旋zig，现重染色
 *       g
 *      / \                 p
 *     pR T3(u)           /   \
 *    / \          =>    xR    gR
 *   xR T2              / \   / \
 *  / \                T0 T1 T2 T3(u)
 * T0 T1
 *
 * 先使用双旋zig-zag，现重染色
 *       g
 *      / \                 x
 *     pR T3(u)           /   \
 *    / \          =>    pR    gR
 *   T0 xR              / \   / \
 *     / \             T0 T1 T2 T3(u)
 *    T1 T2
 * 注：RR-1变换前后，T0~T1向上的第一个黑节点仍为子树根节点，
 * 故变换前后，所有节点高度不变。
 *
 * RR-2: p的兄弟节点为红（即子树T3的根节点u为红），共分4种情况，这里画出2种，另两种完全对称
 * 重新染色，递归检测g的双红问题
 *        g                   gR
 *      /   \               /   \
 *     pR   T3(uR)         p    T3(u)
 *    / \          =>     / \
 *   xR T2               xR T2
 *  / \                 / \
 * T0 T1               T0 T1
 *
 *       g                   gR
 *      / \                 / \
 *     pR T3(uR)           p  T3(u)
 *    / \          =>     / \
 *   T0 xR               T0 xR
 *     / \                 / \
 *    T1 T2               T1 T2
 *
 * </pre>
 *
 * @param x: 新插入的节点
 * @return
 * @retval None
 */
template <typename T>
void RedBlackTree<T>::solve_double_red(BinNode<T>* x)
{
    if (BN_IsRoot(*x))
    {
        x->color = RBColor::Black;
        this->m_root->height++;         // 变成黑节点，高度加1
        return;
    }
    BinNode<T>* p = x->parent;
    if (BN_IsBlack(p))                  // p为黑节点，则没有双红问题
        return;
    BinNode<T>* g = p->parent;          // p为红节点，必有黑父节点
    BinNode<T>* u = BN_IsLeftChild(*p) ? g->right : g->left;

    if (BN_IsBlack(u))
    {
        // RR-1
        BinNode<T>* n = PtrChildOfParent(*g);
                                        // 获取g在父节点的孩子节点指针
        n = this->rotate_at(x);
        n->color = RBColor::Black;
        n->left->color = RBColor::Red;
        n->right->color = RBColor::Red;
    }
    else
    {
        // RR-2 重新染色
        // u原来为红节点，故一定不为nullptr
        p->color = RBColor::Black;
        p->height ++;                   // 由红转黑，高度加1
        u->color = RBColor::Black;
        u->height ++;                   // 由红转黑，高度加1
        if (!BN_IsRoot(*g))
            g->color = RBColor::Red;    // 若g不是根节点，需要转红，继续检测双红问题
        solve_double_red(g);
    }
}

template <typename T>
void RedBlackTree<T>::solve_double_black(BinNode<T>* x)
{

}

/*!
 * @brief 插入节点
 *
 * @param e: 待插入目标
 * @return
 * @retval None
 */
template <typename T>
BinNode<T>* RedBlackTree<T>::insert(const T& e)
{
    BinNode<T>*& x = this->search(e);       // 使用BinSearchTree::search()
    if (x)
        return x;
    x = new BinNode<T>(e, this->m_hot, nullptr, nullptr, -1);   // 以m_hot为父节点，高度为-1，默认为红节点
    this->m_size ++;
    solve_double_red(x);

    // 无论原树中是否有e，返回时总有x->data == e
    return x ? x : this->m_hot->parent;
}

/*!
 * @brief 删除节点
 *
 * @param e: 待插入目标
 * @return
 * @retval None
 */
template <typename T>
bool RedBlackTree<T>::remove(const T& e)
{
    BinNode<T>*& x = this->search(e);
    if (!x) return false;

    //this->remove_at(x, this->m_hot);

}


/*! @} */

} /* dsa */

#endif /* ifndef _REDBLACK_TREE_H */

