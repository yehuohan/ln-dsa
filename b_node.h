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

#ifndef _B_NODE_H
#define _B_NODE_H

#include "vector.h"

namespace dsa
{

/*!
 * @addtogroup Tree
 * @{
 */

/*!
 * @brief b-tree节点类
 *
 * <pre>
 * key为关键码节点，也即数据节点，child为子节点
 * key和child排列如下：一个key对应左右两个子节点
 *
 * key       [0]  [1]  [2]  [3]      =>   *[k0]*[k1]*[k2]*[k3]*
 * child  [0]  [1]  [2]  [3]  [4]         紧凑表示：'*'代表key两则的子节点child
 * b-树(b-tree)阶次为m(这里为5)， 则分支数(子节点) <= m，关键码 <= m-1
 *
 * 约定关键码数为n，则分支数为n+1，
 * 内部节点的分支数n+1不能太少，即有
 * 树根：    2 <= n+1 <= m
 * 其余：⌈m/2⌉ <= n+1 <= m ，⌈⌉为取上整
 * 
 * </pre>
 *
 */
template <typename T>
struct BTNode
{
    BTNode<T>*              parent;
    dsa::Vector<T>          key;    /**< 关键码，即节点数据 */
    dsa::Vector<BTNode<T>*> child;  /**< 分支，即子节点 */

    /*!
     * @brief b-tree节点构造函数
     *
     * 此构造函数默认插入一个指向nullptr的空节点，即分支数为m时，关键码m-1。
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
     * @param e: 节点数据
     * @param lc,rc: 两个孩子
     * @return
     * @retval None
     */
    BTNode(const T& e, BTNode<T>* lc = nullptr, BTNode<T>* rc = nullptr)
    {
        this->parent = nullptr;
        this->key.insert(0, e);
        this->child.insert(0, lc);
        this->child.insert(1, rc);
        if (lc) lc->parent = this;
        if (rc) rc->parent = this;
    }

    ~BTNode()
    {
        for (int k = 0; k < this->child.size(); k ++)
        {
            if (this->child[k])
                delete this->child[k];
        }
    }
};

/*! @} */

} /* dsa */

#endif /* ifndef _B_NODE_H */
