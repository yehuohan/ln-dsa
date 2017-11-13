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

template <typename T>
BinNode<T>* RedBlackTree<T>::insert(const T& e)
{

}

template <typename T>
bool RedBlackTree<T>::remove(const T& e)
{

}


/*! @} */

} /* dsa */

#endif /* ifndef _REDBLACK_TREE_H */

