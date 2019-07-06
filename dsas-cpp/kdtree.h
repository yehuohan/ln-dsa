//==============================================================================
/*!
 * @file kdtree.h
 * @brief kd树
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef DSAS_KDTREE_H
#define DSAS_KDTREE_H

#include "share/compare.h"
#include "vector.h"
#include "array.h"

namespace dsa
{

/*!
 * @addtogroup TKDTree
 *
 * @{
 */

template <typename T, int K> struct KdNode;
/** kd树节点指针类型 */
template <typename T, int K> using KdNodePtr = struct KdNode<T,K>*;
/** kd树节点数据 */
template <typename T, int K> using KdNodeData = dsa::Array<T,K>;

/*!
 * @brief kd树节点
 * K为维度大小
 */
template <typename T, int K>
struct KdNode
{
    KdNodeData<T,K> data;       /**< 节点数据，共K个，即K维数据 */
    int             dim;        /**< 节点分割维度，范围[0,k) */
    KdNodePtr<T,K>  parent;
    KdNodePtr<T,K>  left;
    KdNodePtr<T,K>  right;

    KdNode(const KdNodeData<T,K>& _data, int _dim,
            KdNodePtr<T,K> p=nullptr, KdNodePtr<T,K> l=nullptr, KdNodePtr<T,K> r=nullptr)
        : data(_data), dim(_dim), parent(p), left(l), right(r) {}

    /** 插入左子节点 */
    KdNodePtr<T,K> insert_left(const KdNodeData<T,K>& e, int d) {return this->left = new KdNode(e, d, this);}
    /** 插入右子节点 */
    KdNodePtr<T,K> insert_right(const KdNodeData<T,K>& e, int d) {return this->right = new KdNode(e, d, this);}
};

/*!
 * @brief kd树类
 * K为维度大小
 */
template <typename T, int K, typename CMP = dsa::Less<T>>
class KdTree
{
protected:
    KdNodePtr<T,K>      m_root;
    int                 m_size;
    int                 m_k;

    //void init_kdnodes(dsa::Vector<dsa::Vector<T>>& ele, int lo, int hi,int d);

public:
    KdTree(): m_k(K), m_size(0),m_root(nullptr) {}

    //void    insert();
    //void    remove();
    //void    search();     // k邻近查找
};

/*! @} */

} /* dsa */
#endif /* ifndef DSAS_KDTREE_H */
