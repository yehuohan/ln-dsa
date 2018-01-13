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
 * 3.其余节点：若为红，则子节点只能为黑，即任何节点的父节点不可能为红
 * 4.外部节点到根节点：途中黑节点数相等
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
 *
 * 新插入节点x为红，其父节点p也为红，即为双红问题；
 * 带有R的节点为红，否则为黑。
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
 * 注：RR-2变换前后，p u高度因为变黑会加1，
 * 而g因为变红，即使子节点p u的高度加1，g的高度仍不变
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
 * x为要删除的节点，且为其所在子树的根节点，r为接替x所在位置的节点;
 * 带有R的节点为红，未做特别说明则为黑；
 * x和r均为黑节点，删除x后，黑高度会受影响，此为双黑问题。
 *
 * [BB-1: s为黑，且s至少有一个红子节点，p可黑可红]
 * 34重构后，再染色；
 * s继承p的颜色；t,p变黑；s,t,p需要更新黑高度。
 * 删除x前后，子树T0~T3到根节点经过的黑节点如下所示：
 * T0-s-p          T0-t-s
 * T1-s-p    =>    T1-t-s
 * T2-s-p          T2-p-s
 * T3-x-p          T3-p-s
 *       p
 *      / \                     s
 *     s  T3[x(r)]            /   \
 *    / \             =>     t     p
 *   tR T2                  / \   / \
 *  / \                    T0 T1 T2 T3
 * T0 T1
 *
 * [BB-2R: s为黑，且s的两个子节点均为黑，p为红]
 * 重新染色；
 * 左边s转红，黑高度减1；右边删除黑节点x，黑高度减1；
 * 但p转黑，故p黑度最后不变。
 *     pR                    p
 *    / \                   / \
 *   s  T2[x(r)]   =>      sR T2[r]
 *  / \                   / \
 * T0 T1                 T0 T1
 *
 * [BB-2B: s为黑，且s的两个子节点均为黑，p为黑]
 * 重新染色，再递归对p进行双黑检测；
 * 左边s转红，黑高度减1；右边删除黑节点x，黑高度减1；
 * 故p的黑高度会减1。
 *     p                     p
 *    / \                   / \
 *   s  T2[x(r)]   =>      sR T2[r]
 *  / \                   / \
 * T0 T1                 T0 T1
 *
 * [BB-3: s为红，s的两个子节点只能为黑]
 * 旋转后，以pR-T1-T2形成的子树转入BB-1或BB-2R；
 * T1的根节点为黑，T2的根节点r为黑；p为红；
 * 故再次递归对r进行双黑修复时，只可能为BB-1或BB-2R。
 *     p                     s
 *    / \                   / \
 *   sR T2[x(r)]   =>   T0(t) pR
 * /   \                     / \
 *T0(t) T1                 T1  T2[r]
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
 * x为待删除的节点，r为接替x所在位置的节点；
 * 带有R的节点为红，否则为黑。
 *
 *   p           p
 *   |           |
 *   xR    =>    r
 *  / \         / \
 * w   r       .....
 *
 *   p           p
 *   |           |
 *   x     =>    r
 *  / \         / \
 * w  rR       .....
 *
 * 若x或r有一个为红，则将r染黑即可;
 * 若x和r均为黑，则需要使用solve_double_black解决双黑问题。
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

    // r为接替x所在位置的节点，r可以为nullptr，m_hot为r的父节点
    BinNodePtr<T> r = remove_at(x, this->m_hot);
    // 没有节点了，则直接返回
    if(!(--this->m_size))
        return true;

    // 删除的是根节点，则r成为新的根节点
    if(!this->m_hot)
    {
        this->m_root->color = RBColor::Black;
        this->update_height(this->m_root);
        return true;
    }

    //若所有祖先的黑深度依然平衡，则无需调整
    if (BN_BlackHeightUpdated(*this->m_hot))
        return true;
    // r为红，只需要染黑即可
    if (BN_IsRed(r))
    {
        r->color = RBColor::Black;
        r->height ++;
        return true;
    }
    // 双黑问题
    solve_double_black(r);
    return true;
}

} /* dsa */

#endif /* ifndef _REDBLACK_TREE_H */

