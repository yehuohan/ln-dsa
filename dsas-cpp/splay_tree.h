
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
 * @addtogroup TSplayTree
 * @{
 */

/*!
 * @brief 伸展树类
 *
 * 局部性：刚被访问的过的数据，极有可能很快现次被访问；
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

/*! @} */


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
 * @brief 查找节点。
 *
 * @param e: 查找目标。
 * @return 返回经过伸展后的树根节点。返回nullptr的唯一情况：树没有任何节点，即空树。
 * @retval None
 */
template <typename T>
BinNode<T>*& SplayTree<T>::search(const T& e)
{
    BinNode<T>* p = search_in(this->m_root, e, this->m_hot = nullptr);
    // 无论是否找到节点，均会进行伸展操作，即没有找到目标节点，也将靠近目标的节点移到树根
    this->m_root = this->splay(p ? p : this->m_hot);
    // 若m_root为nullptr（即没有查找到目标e，且m_hot也为nullptr）
    // 则一定是空树的情况（非空树，即使没有查找到目录，m_hot也不会为nullptr）
    return this->m_root;
}

/*!
 * @brief 插入节点
 *
 * @param e: 待插入目标。
 * @return
 * @retval None
 */
template <typename T>
BinNode<T>* SplayTree<T>::insert(const T& e)
{
    // 如果是空树，直接插入节点即可
    if (!this->m_root)
    {
        this->m_size++;
        this->m_root = new BinNode<T>(e, nullptr);
        return this->m_root;
    }

    // 因为不是空树,返回的x不可以为nullptr
    // search 返回经过伸展后的树根节点
    if (this->search(e)->data == e) return this->m_root;

    BinNode<T>* r = this->m_root;
    this->m_root = new BinNode<T>(e, nullptr);
    this->m_size++;

    // 确定新插入节点的位置
    if (e < r->data)
    {
        attach_left(this->m_root, r->left);
        attach_right(this->m_root, r);
        r->parent = this->m_root;
        r->left = nullptr;

    }
    else if (r->data < e)
    {
        attach_right(this->m_root, r->right);
        attach_left(this->m_root, r);
        r->parent = this->m_root;
        r->right = nullptr;
    }
    this->update_height_above(r);

    return this->m_root;
}

/*!
 * @brief 删除节点。
 *
 * @param e: 删除目标。
 * @return
 * @retval None
 */
template <typename T>
bool SplayTree<T>::remove(const T& e)
{
    // 空树直接返回
    if (!this->m_root) return false;
    // 没有找到目标
    if (this->search(e)->data != e) return false;

    // 删除目标节点（经过伸展，已经移到了根节点）
    BinNode<T>* s = this->m_root;
    if (!BN_HasLeftChild(*this->m_root))
    {
        this->m_root = this->m_root->right;
        if (this->m_root) this->m_root->parent = nullptr;
    }
    else if (!BN_HasRightChild(*this->m_root))
    {
        this->m_root = this->m_root->left;
        if (this->m_root) this->m_root = nullptr;
    }
    else
    {
        BinNode<T>* lt = this->m_root->left;
        // 暂时分离左子树
        this->m_root->left = nullptr;
        lt->parent = nullptr;
        // 只保留右子树
        this->m_root = this->m_root->right;
        this->m_root->parent = nullptr;
        // 以原树根为目标，在原右子树做一次（必定失败的）查找，
        // 原右子树中的最大值经过伸展后，会移到原右子树的根节点
        this->search(s->data);
        // 再将原左子树连接到根节点
        this->m_root->left = lt;
        lt->parent = this->m_root;
    }

    delete s;
    this->m_size--;
    if (this->m_root) this->update_height(this->m_root);

    return true;
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

// namespace dsa end
}

#endif /* ifndef _SPLAY_TREE_H */
