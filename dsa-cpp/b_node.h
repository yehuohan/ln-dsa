//==============================================================================
/*!
 * @file b_node.h
 * @brief b-树(b-tree)节点类
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef DSAS_B_NODE_H
#define DSAS_B_NODE_H

#include "vector.h"

namespace dsa
{

/*!
 * @addtogroup TBTree
 * @{
 */

template <typename T> struct BTNode;
template <typename T>
using BTNodePtr = struct BTNode<T>*;

/*!
 * @brief b-树(b-tree)节点类
 *
 * <pre>
 * key为关键码节点，也即数据节点，child为子节点
 * key和child排列如下：一个key对应左右两个子节点
 *
 * key       [0]  [1]  [2]  [3]      =>   *[k0]*[k1]*[k2]*[k3]*
 * child  [0]  [1]  [2]  [3]  [4]         紧凑表示：'*'代表key两则的子节点child
 * b-树(b-tree)阶次为m(这里为5)， 则分支数(子节点) <= m，关键码 <= m-1；
 * 且分支数(子节点) = 关键码数+1 恒成立。
 *
 * 约定关键码数为n，则分支数为n+1，
 * 内部节点的分支数n+1不能太少，即有
 * 树根：        2 <= n+1 <= m
 * 其余：ceil(m/2) <= n+1 <= m ，ceil为取上整
 * 故 b-tree 也称做 (⌈m/2⌉，m)-tree 。
 * </pre>
 *
 */
template <typename T> struct BTNode
{
    BTNodePtr<T>                parent;
    dsa::Vector<T>              key;    /**< 关键码，即节点数据 */
    dsa::Vector<BTNodePtr<T> >  child;  /**< 分支，即子节点 */

    /*!
     * @brief b-tree节点构造函数
     *
     * 构造函数默认插入一个指向nullptr的空节点，即分支数为m时，关键码m-1。
     * 同时，当同时向key和child 追加 关键码和节点时，仍满足分支数为m，关键码数为m-1。
     *
     * @param None
     * @return
     * @retval None
     */
    BTNode(){parent = nullptr; child.insert(0, nullptr); }

    /*!
     * @brief b-tree节点构造函数
     *
     * 构造函数默认插入一个指向nullptr的空节点，即分支数为m时，关键码m-1。
     * b-树(b-tree)阶次为m，则key的容量 <= m-1， child的容量 <= m。
     * 因为Vector的size==capacity时就扩展容，所以为使Vector不用护展容量，key和child的容量均+1。
     *
     * @param m: btree的阶数
     * @return
     * @retval None
     */
    BTNode(int m) : key(m-1+1), child(m+1) {parent = nullptr; child.insert(0, nullptr); }

    /*!
     * @brief b-tree节点构造函数
     *
     * 初始化时插一个关键码，和两条分支。
     *
     * @param e: 节点数据
     * @param lc,rc: 两个孩子
     * @return
     * @retval None
     */
    BTNode(const T& e, BTNodePtr<T> lc = nullptr, BTNodePtr<T> rc = nullptr)
    {
        this->parent = nullptr;
        this->key.insert(0, e);
        this->child.insert(0, lc);
        this->child.insert(1, rc);
        if (lc) lc->parent = this;
        if (rc) rc->parent = this;
    }

    /*!
     * @brief b-tree节点构造函数
     *
     * 初始化时插一个关键码，和两条分支。
     * b-树(b-tree)阶次为m，则key的容量 <= m-1， child的容量 <= m。
     * 因为Vector的size==capacity时就扩展容，所以为使Vector不用护展容量，key和child的容量均+1。
     *
     * @param m: btree的阶数
     * @param e: 节点数据
     * @param lc,rc: 两个孩子
     * @return
     * @retval None
     */
    BTNode(int m, const T& e, BTNodePtr<T> lc = nullptr, BTNodePtr<T> rc = nullptr) : key(m-1+1), child(m+1)
    {
        this->parent = nullptr;
        this->key.insert(0, e);
        this->child.insert(0, lc);
        this->child.insert(1, rc);
        if (lc) lc->parent = this;
        if (rc) rc->parent = this;
    }
};

/*! @} */

} /* dsa */

#endif /* ifndef DSAS_B_NODE_H */
