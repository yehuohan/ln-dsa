
//==============================================================================
/*!
 * @file splay_tree.h
 * @brief 伸展树类
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _SPLAY_TREE_H
#define _SPLAY_TREE_H

#include "binary_search_tree.h"

namespace dsa
{

/*!
 * @addtogroup Tree
 * @{
 */

/*!
 * @brief 伸展树类
 *
 */
template <typename T>
class SplayTree : public BinSearchTree<T>
{
public:
    BinNode<T>*& search(const T& e);
    BinNode<T>*  insert(const T& e);
    bool         remove(const T& e);

protected:
    BinNode<T>* splay(BinNode<T>*);
};

template <typename T>
BinNode<T>*& SplayTree<T>::search(const T& e)
{
    BinNode<T>* x;
    return x;
}

template <typename T>
BinNode<T>* SplayTree<T>::insert(const T& e)
{
    return nullptr;
}

template <typename T>
bool SplayTree<T>::remove(const T& e)
{
    return true;
}

/*!
 * @brief 添加左子节点
 *
 * @param p: 父节点
 * @param c: 子节点
 * @return
 * @retval None
 */
template <typename T>
inline void attach_left(BinNode<T>* p, BinNode<T>* c)
{
    p->left = c;
    if (c) c->parent = p;
}

/*!
 * @brief 添加右子节点
 *
 * @param p: 父节点
 * @param c: 子节点
 * @return
 * @retval None
 */
template <typename T>
inline void attach_right(BinNode<T>* p, BinNode<T>* c)
{
    p->right = c;
    if (c)
        c->parent = p;
}

/*!
 * @brief 对节点进行伸展
 *
 * <pre>
 * 双层伸展：
 * zag-zag (先旋转gp，再旋转gv)      | zig-zig(先旋转gp，再旋转gv)
 *   g                       v       |      g                       v
 * /   \                   /   \     |    /   \                    / \
 * T0  p        =>        p    T3    |    p   T3       =>         T0  p
 *    / \                / \         |   / \                         / \
 *   T1 v               g  T2        |   v T2                       T1  g
 *     / \             / \           |  / \                            / \
 *    T2 T3           T0 T1          | T0 T1                          T2 T3
 *                                   |
 * zig-zag(先旋转pv，再旋转gv)       | zag-zig(先旋转pv，再旋转gv)
 *   g                       v       |      g                       v
 * /   \                   /   \     |    /   \                   /   \
 * T0   p                 g     p    |   p    T3                 p     g
 *    /   \              / \   / \   | /   \                    / \   / \
 *   v    T3    =>      T0 T1 T2 T3  | T0   v          =>      T0 T1 T2 T3
 *  / \                              |     / \
 * T1 T2                             |    T1 T2
 *
 * 单层伸展：
 * zig:                              | zag:
 *     p                   v         |     p                   v
 *    / \                 / \        |    / \                 / \
 *   v  T2      =>       T0  p       |   T0  v       =>      p  T2
 *  / \                     / \      |      / \             / \
 * T0  T1                  T1 T2     |     T1  T2          T0 T1
 * </pre>
 *
 * @param v: 待展展的节点
 * @return
 * @retval None
 */
template <typename T>
BinNode<T>* SplayTree<T>::splay(BinNode<T>* v)
{
    if (!v) return nullptr;
    BinNode<T>* p;
    BinNode<T>* g;

    // 双层伸展，伸展完成后，v将成为子树的根节点
    while((p = v->parent) && (g = p->parent))
    {
        BinNode<T>* gg = g->parent;
        if (BN_IsLeftChild(*v))
        {
            if (BN_IsLeftChild(*p))
            {
                // zig-zig
                attach_left(p, v->right);
                attach_left(g, p->right);
                attach_right(v, p);
                attach_right(p, g);
            }
            else
            {
                // zig-zag
                this->connect34(g, v, p,
                        g->left, v->left, v->right, p->right);
            }
        }
        else
        {
            if (BN_IsRightChild(*p))
            {
                // zag-zag
                attach_right(p, v->left);
                attach_right(g, p->left);
                attach_left(v, p);
                attach_left(p, g);
            }
            else
            {
                // zag-zig
                this->connect34(g, v, g,
                        p->left, v->left, v->right, g->right);
            }

        }

        // 将新的子树接入到原树的位置
        if (!gg)
            v->parent = nullptr;    // 成为树根节点
        else
            (g == gg->left) ? attach_left(gg, v) : attach_right(gg, v);
                                    // 插入到原树作为左子树或右子树

        this->update_height(g);
        this->update_height(p);
        this->update_height(v);
    }

    // 单层伸展，最多一次旋转
    if ((p = v->parent))
    {
        if (BN_IsLeftChild(*v))
        {
            attach_left(p, v->right);
            attach_right(v, p);
        }
        else
        {
            attach_right(p, v->left);
            attach_left(v, p);
        }
    }

    // v成为树的根节点
    v->parent = nullptr;
    return v;
}

/*! @} */

// namespace dsa end
}

#endif /* ifndef _SPLAY_TREE_H */
