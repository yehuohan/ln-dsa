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
 * @addtogroup TRedBlackTree
 *
 * @{
 */

/*!
 * @brief 红黑树类
 *
 *<pre>
 * 1.树根：必为黑
 * 2.外部节点(类似于b-tree中的external nodes，值为nullptr)：均为黑
 * 3.其余节点：若为红，则子节点只能为黑，即任何红节点的父节点不可能为红
 * 4.从任一节点到其每个（子孙）外部节点：途中路径经过的黑节点数相同；
 *
 * 红黑树与(2,4)b-tree等价；
 * b-tree是平衡的，故红黑树也是平衡的；
 * 相对于avl树，红黑树不需要额外的平衡因子。
 *</pre>
 *
 */
template <typename T>
class RedBlackTree : public BinSearchTree<T>
{
public:
    BinNodePtr<T>   insert(const T&);
    bool            remove(const T&);

protected:
    void            solve_double_red(BinNodePtr<T>);
    void            solve_double_black(BinNodePtr<T>);
    int             update_height(BinNodePtr<T>);
};

/*! @} */


/*!
 * @brief 更新节点高度
 *
 * 红黑树的高度，只对黑节点计数。
 * 此函数是对基类BinTree中的update_height的重写，
 * 故BinSearchTree<T>::connect34中将会调用这里的update_height进行高度更新。
 *
 * @param x: 待更新高度的节点
 * @return
 * @retval None
 */
template <typename T>
int RedBlackTree<T>::update_height(BinNodePtr<T> x)
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
 * 设新插入节点为x，x的父节点为p，p的父节点为g，x的叔父节点为u(也即p的兄弟节点)；
 * 带有R的节点为红，未做特殊说明则为黑；
 * x为红，p也为红，即为双红问题。
 *     (1)        (2)        (3)        (4)
 *      g          g          g          g
 *     / \        / \        / \        / \
 *    pR  u      pR  u      u   pR     u   pR
 *   /            \            /            \
 *  xR             xR         xR             xR
 * 普遍情况有以上4种，且均是两两对称形式，调整方法是类似的；
 * 还有特殊情况就是，新插入的节点x就是根节点。
 *
 * 针对不同的情况，进行相应的调整（以第(1)(2)种情况为例，(3)(4)情况对称，调整类似）：
 *
 * RR-1: p为红（则g必为黑），u为黑（子树T3的根节点为u）
 * 先用BinSearchTree::rotate_at的单旋zig，再重染色 | 先用BinSearchTree::rotate_at的双旋zig-zag，再重染色
 *       g                                         |      g
 *      / \                 p                      |     / \                 x
 *     pR T3[u]           /   \                    |    pR T3[u]           /   \
 *    / \          =>    xR    gR                  |   / \          =>    pR    gR
 *   xR T2              / \   / \                  |  T0 xR              / \   / \
 *  / \                T0 T1 T2 T3(u)              |    / \             T0 T1 T2 T3(u)
 * T0 T1                                           |   T1 T2
 *
 * 调整前，T0~T3向上的第一个黑节点为子树根节点g；
 * 调整后，T0~T3向上的第一个黑节点为仍为子树根节(p或x)；
 * 故调整前后，子树根节点到（子孙）外部节点所经过的黑节点数不变。
 *
 * RR-2: p为红（则g必为黑），u为红（子树T3的根节点为u）
 * 重新染色，递归检测g的双红问题
 *        g                   gR      |     g                   gR
 *      /   \               /   \     |    / \                 / \
 *     pR   T3[uR]         p    T3[u] |   pR T3[uR]           p  T3[u]
 *    / \          =>     / \         |  / \          =>     / \
 *   xR T2               xR T2        | T0 xR               T0 xR
 *  / \                 / \           |   / \                 / \
 * T0 T1               T0 T1          |  T1 T2               T1 T2
 *
 * 调整前后，pu变黑，但g变红，故从g到其每个（子孙）外部节点上的黑节点数量仍不变；
 * 但因为g的父节点可能为红，故需要继续对g进行双红检测。
 *
 * </pre>
 *
 * @param x: 新插入的节点
 * @return
 * @retval None
 */
template <typename T>
void RedBlackTree<T>::solve_double_red(BinNodePtr<T> x)
{
    if (BN_IsRoot(*x))
    {
        x->color = RBColor::Black;
        this->m_root->height++;         // 变成黑节点，高度加1
        return;
    }
    BinNodePtr<T> p = x->parent;
    if (BN_IsBlack(p))                  // p为黑节点，则没有双红问题
        return;
    BinNodePtr<T> g = p->parent;          // p为红节点，必有黑父节点
    BinNodePtr<T> u = BN_IsLeftChild(*p) ? g->right : g->left;

    if (BN_IsBlack(u))
    {
        // RR-1
        g->color = RBColor::Red;
       // x,p同侧，即同为左孩子或同为右孩子
        if (BN_IsLeftChild(*x) == BN_IsLeftChild(*p))
            p->color = RBColor::Black;
        else
            x->color = RBColor::Black;

        BinNodePtr<T>& n = RefFromParent(*g); // 获取g在父节点的孩子节点指针
        n = this->rotate_at(x);             // 34重构中会更新高度，故重染色需要在rotate_at之前进行
        //n->color = RBColor::Black;
        //n->left->color = RBColor::Red;
        //n->right->color = RBColor::Red;
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
        solve_double_red(g);            // 若g是根节点，在递归调用中，高度会得到更新
    }
}

/*!
 * @brief 修复双黑问题
 *
 * <pre>
 * 设x为待删除的节点，r为接替x所在位置的节点（且r为其所在子树的根节点），p为x父节点，s为x兄弟节点；
 * 带有R的节点为红，未做特别说明则为黑；
 * 根据remove_at算法，在删除x时，x必定最多只有一个子树分支。
 *      p              p
 *     / \            / \
 *    s   x      =>  s   T[r]
 *         \
 *          T[r]
 * x和r均为黑，删除节点x后，节点p-r所在路径的黑节点数少了1，此即为双黑问题。
 * 双黑调整原理：通过旋转和染色，使得节点p-r所在路径黑节点数加1；
 *                             或使得节点p-s所在路径黑节点数减1，再递归调整。
 *
 * 针对不同的双黑情况，进行相应的调整：
 *
 * [BB-1: s为黑，且s至少有一个红子节点，p可黑可红]
 * 34重构后，再染色，最后更新s,t,p需要更新黑高度：
 * s继承p的颜色，tp变黑              | t继承p的颜色，sp变黑
 *       p                           |     p
 *      / \                s         |    / \                t
 *     s   T3[r]         /   \       |   s  T3[r]          /   \
 *    / \          =>   t     p      |  / \          =>   s     p
 *   tR T2             / \   / \     | T0  tR            / \   / \
 *  / \               T0 T1 T2 T3[r] |    / \           T0 T1 T2 T3[r]
 * T0 T1                             |   T1 T2
 *
 * 调整前后，T0~T3到子树根节点经过的黑节点如下所示：
 * T0 - s - p          T0 - t - s    | T0 - s - p          T0 - s - t
 * T1 - s - p    =>    T1 - t - s    | T1 - s - p    =>    T1 - s - t
 * T2 - s - p          T2 - p - s    | T2 - s - p          T2 - p - t
 * T3 - p              T3 - p - s    | T3 - p              T3 - p - t
 * 可以看到，在调整后，节点p-r所在路径黑节点数加了1（即节点s或t）；
 * 且不改变T0~T2所在路径黑节点的数量。
 *
 * [BB-2R: s为黑，且s两个子节点均为黑，p为红]
 * 重染色：s变红，p变黑
 *     pR                    p
 *    / \                   / \
 *   s  T2[r]      =>      sR T2[r]
 *  / \                   / \
 * T0 T1                 T0 T1
 * s变红，p-s所在路径黑节点数减1；
 * p变黑，p-s和p-r所在路径黑节点数均加1；
 * 最终，p-s和p-r所在路径黑节点数不变；
 *
 * [BB-2B: s为黑，且s两个子节点均为黑，p为黑]
 * 重染色（s变红），再递归对p进行双黑检测；
 *     p                     p
 *    / \                   / \
 *   s  T2[r]      =>      sR T2[r]
 *  / \                   / \
 * T0 T1                 T0 T1
 * s变红，p-s所在路径黑节点数减1；
 * p颜色不变，所以p-s和p-r所在路径的黑节点数均减1，故需要对p继续进行双黑检测。
 *
 * [BB-3: s为红，则p必为黑，s子节点必为黑]
 * 先旋转：t选取与s同侧的（s为p的左子节点，则t也选s的左子节点），这样只需要一次旋转；
 * 再染色：s变黑，p变红；
 * 再对r进行双黑检测：因为p为红，故以pR-T2-T3形成的子树必为BB-1或BB-2R情况。
 *       p
 *      / \                s
 *     sR T3[r]    =>    /   \
 *    / \               t     pR
 *   t  T2             / \   / \
 *  / \               T0 T1 T2 T3[r]
 * T0 T1
 * p变红，p-r所在路径黑节点数再次减少了1，共减少了2；
 * s变成p的父节点，p-r所在路径黑节点数加1，共减少了1，故需要对r继续进行双黑检测。
 *
 * </pre>
 *
 * <pre>
 * BB-1 ：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
 * BB-2R：2次颜色翻转，2次黑高度更新，0次旋转，不再递归
 * BB-2B：1次颜色翻转，1次黑高度更新，0次旋转，需要递归
 * BB-3 ：2次颜色翻转，2次黑高度更新，1次旋转，转为BB-1或BB-2R
 * </pre>
 *
 * @param r: 被删除节点所在位置的新节点
 * @return
 * @retval None
 */
template <typename T>
void RedBlackTree<T>::solve_double_black(BinNodePtr<T> r)
{
    // 如果r为nullptr，则r的父节点为m_hot
    BinNodePtr<T> p = r ? r->parent : this->m_hot;
    // r为根节点
    if (!p)
        return;
    // r的兄弟节点
    BinNodePtr<T> s = (r == p->left) ? p->right : p->left;

    if (BN_IsBlack(s))  // s为黑
    {
        BinNodePtr<T> t = nullptr;
        if (BN_IsRed(s->left)) t = s->left;
        else if (BN_IsRed(s->right)) t = s->right;
        if (t)          // s至少有一个红子节点
        {
            // BB-1
            RBColor clr = p->color;
            BinNodePtr<T>& n = RefFromParent(*p);
            // 因为34重构前，未进行颜色设置，故rotate_at中的高度更新无效
            n = this->rotate_at(t);
            // 重染色后，需要重新计算黑高度
            if (BN_HasLeftChild(*n))
            {
                n->left->color = RBColor::Black;
                this->update_height(n->left);
            }
            if (BN_HasRightChild(*n))
            {
                n->right->color = RBColor::Black;
                this->update_height(n->right);
            }
            n->color = clr;
            this->update_height(n);
        }
        else            // s两个子节点均为黑
        {
            s->color = RBColor::Red;        // s转红，高度减1
            s->height--;
            if (BN_IsRed(p))                // p为红
            {
                // BB-2R
                p->color = RBColor::Black;  //p转黑，但黑高度不变
            }
            else                            // p为黑
            {
                // BB-2B
                p->height--;                //p保持黑，但黑高度下降
                solve_double_black(p);
            }
        }
    }
    else                // s为红，两个子节点则一定为黑
    {
        // BB-3
        p->color = RBColor::Red;
        s->color = RBColor::Black;
        BinNodePtr<T> t = (BN_IsLeftChild(*s)) ? s->left : s->right;
                        // 取t与s取同侧
        this->m_hot = p;
        BinNodePtr<T>& n = RefFromParent(*p);
        n = this->rotate_at(t);
        // 递归修正r处的双黑问题
        solve_double_black(r);
    }
}

/*!
 * @brief 插入节点
 *
 * @param e: 待插入目标
 * @return
 * @retval None
 */
template <typename T>
BinNodePtr<T> RedBlackTree<T>::insert(const T& e)
{
    BinNodePtr<T>& x = this->search(e);       // 使用BinSearchTree::search()
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
 * <pre>
 * 使用binary_search_tree.h中的remove_at删除节点；
 * 设x为待删除的节点，r为接替x所在位置的节点（且r为其所在子树的根节点）；
 * 带有R的节点为红，未做特别说明则为黑；
 * 根据remove_at算法，在删除x时，x必定最多只有一个子树分支。
 *
 *   x红，r黑，p黑         |  x黑，r红，p红或黑
 *    p            p       |    p            p
 *   / \          / \      |   / \          / \
 *  s   xR   =>  s   T[r]  |  s   x    =>  s   T[r]
 *       \                 |       \
 *        T[r]             |        T[rR]
 *
 * 若x和r只有一个为红，则将r染黑即可；
 * 若x和r均为黑，删除x后，节点p-r所在路径的黑节点数减1，需要使用solve_double_black解决双黑问题。
 *
 * </pre>
 *
 * @param e: 待插入目标
 * @return
 * @retval None
 */
template <typename T>
bool RedBlackTree<T>::remove(const T& e)
{
    BinNodePtr<T>& x = this->search(e);
    if (!x)
        return false;

    // 因为是先删除x，再进行调整，故先保存好x的颜色
    dsa::RBColor xclr = x->color;
    // r为接替x所在位置的节点，r可以为nullptr，m_hot为r的父节点
    BinNodePtr<T> r = this->remove_at(x, this->m_hot);

    // 没有节点了，则直接返回
    if(!(--this->m_size))
        return true;
    // 删除的是根节点，则所有路径少了一个黑节点，则r即为新root节点
    if(!this->m_hot)
    {
        this->m_root->color = RBColor::Black;
        this->update_height(this->m_root);
        return true;
    }

#if 1
    // x为黑，r为红，r的颜色和高度需要调整
    if (xclr == dsa::RBColor::Black && BN_IsRed(r))
    {
        r->color = RBColor::Black;
        r->height ++;
    }
    // x为红，r为黑，则r颜色和高度无需要变化（因为x的黑高度和r的黑高度相等）
    else if (xclr == dsa::RBColor::Red && BN_IsBlack(r))
    { }
    // x为黑，r为黑（x,r不可能同时为红）
    else
        solve_double_black(r);
    return true;

#else

    //若所有祖先的黑深度依然平衡，则无需调整
    if (BN_BlackHeightUpdated(*this->m_hot))
        return true;
    // r为红，则需要染黑
    if (BN_IsRed(r))
    {
        r->color = RBColor::Black;
        r->height ++;
        return true;
    }
    // r为黑，双黑问题
    solve_double_black(r);
    return true;
#endif
}

} /* dsa */

#endif /* ifndef _REDBLACK_TREE_H */

