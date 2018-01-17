
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
#include "share/compare.h"

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
    BinNodePtr<T>&  search(const T& e);
    BinNodePtr<T>   insert(const T& e);
    bool            remove(const T& e);

protected:
    BinNodePtr<T>   splay(BinNodePtr<T>);
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
inline void attach_left(BinNodePtr<T> p, BinNodePtr<T> c)
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
inline void attach_right(BinNodePtr<T> p, BinNodePtr<T> c)
{
    p->right = c;
    if (c) c->parent = p;
}

/*!
 * @brief 查找节点。
 *
 * @param e: 查找目标。
 * @return 返回经过伸展后的树根节点。返回nullptr的唯一情况：树没有任何节点，即空树。
 * @retval None
 */
template <typename T>
BinNodePtr<T>& SplayTree<T>::search(const T& e)
{
    BinNodePtr<T> p = search_in(this->m_root, e, this->m_hot = nullptr);
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
BinNodePtr<T> SplayTree<T>::insert(const T& e)
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
    if (dsa::is_equal(this->search(e)->data, e)) return this->m_root;

    BinNodePtr<T> r = this->m_root;
    this->m_root = new BinNode<T>(e, nullptr);
    this->m_size++;

    // 确定新插入节点的位置
    if (dsa::less_than(e, r->data))
    {
        attach_left(this->m_root, r->left);
        attach_right(this->m_root, r);
        r->parent = this->m_root;
        r->left = nullptr;

    }
    else if (dsa::less_than(r->data, e))
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
    if (dsa::not_equal(this->search(e)->data, e)) return false;

    // 删除目标节点（经过伸展，已经移到了根节点）
    BinNodePtr<T> s = this->m_root;
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
        BinNodePtr<T> lt = this->m_root->left;
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
 *
 * 伸展的目的是使目标节点向上移，直至成为根节点root；
 * 优先双层伸展，直至最后只剩下一层，则执行单层伸展。
 *
 * (1)双层伸展
 * zag-zag(先zag旋转gp，再zag旋转pv) | zig-zig(先zig旋转gp，再zig旋转pv)
 *   g                       v       |        g                  v
 * /   \                   /   \     |      /   \               / \
 * T0   p       =>        p    T3    |     p    T3     =>     T0   p
 *     / \               / \         |    / \                     / \
 *    T1  v             g  T2        |   v  T2                   T1  g
 *       / \           / \           |  / \                         / \
 *      T2 T3         T0 T1          | T0 T1                       T2 T3
 *                                   |
 * (与AVL旋转相同)                   | (与AVL旋转相同)
 * zig-zag(先zig旋转pv，再zag旋转gv) | zag-zig(先zag旋转pv，再zig旋转gv)
 * 双旋:                             |  双旋:
 *   g                       v       |      g                       v
 * /   \                   /   \     |    /   \                   /   \
 * T0   p                 g     p    |   p    T3                 p     g
 *     / \               / \   / \   |  / \                     / \   / \
 *    v  T3     =>      T0 T1 T2 T3  | T0  v           =>      T0 T1 T2 T3
 *   / \                             |    / \
 *  T1 T2                            |   T1 T2
 *
 * (2)单层伸展
 * zig:                              | zag:
 *     p                   v         |     p                   v
 *    / \                 / \        |    / \                 / \
 *   v  T2      =>       T0  p       |   T0  v       =>      p  T2
 *  / \                     / \      |      / \             / \
 * T0  T1                  T1 T2     |     T1  T2          T0 T1
 *
 * (3)伸展效果
 * 查找'1':
 * 伸过数次伸展，'1'成为了根节点，而树的高度也减小了一半；
 *               8              8            8             8             1
 *              /              /            /             /      =>       \
 *             7              7            7             1   (伸展1,8)     8
 *            /              /            /               \               /
 *           6              6            6                 6             6
 *          /              /            /     =>          / \           / \
 *         5              5            1  (伸展1,6,7)    4   7         4   7
 *        /              /              \               / \           / \
 *       4              4     =>         4             2   5         2   5
 *      /              /  (伸展1,4,5)   / \             \             \
 *     3              1                2   5             3             3
 *    /       =>       \                \
 *   2   (伸展1,2,3)    2                3
 *  /                    \
 * 1                      3
 *
 * 查找'3':
 * 伸过数次伸展，'3'成为了根节点，'1'仍在根节点附近，树的高度再度减小一半；
 *      1                   1                 1                   3
 *       \                   \                 \        =>     /     \
 *        8                   8                 3  (伸展1,3)  1       6
 *       /                   /                 / \             \    /   \
 *      6                   6        =>       2   6             2  4     8
 *     / \                 / \  (伸展3,6,8)  /   \               \      /
 *    4   7               3   7             4     8               5    7
 *   / \        =>       / \                 \   /
 *  2   5  (伸展3,2,4)  2   4                 5 7
 *   \                   \
 *    3                   5
 *
 *
 * </pre>
 *
 * @param v: 待伸展的节点
 * @return
 * @retval None
 */
template <typename T>
BinNodePtr<T> SplayTree<T>::splay(BinNodePtr<T> v)
{
    if (!v) return nullptr;
    BinNodePtr<T> p;
    BinNodePtr<T> g;

    // 双层伸展，伸展完成后，v将成为子树的根节点
    while((p = v->parent) && (g = p->parent))
    {
        BinNodePtr<T> gg = g->parent;
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

} /* dsa */

#endif /* ifndef _SPLAY_TREE_H */
