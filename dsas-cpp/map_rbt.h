
//==============================================================================
/*!
 * @file map_rbt.h
 * @brief 基于红黑树实现的Map结构
 *
 * @date 2019-07-03
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _MAP_RBT_H
#define _MAP_RBT_H

#include "redblack_tree.h"
#include "share/entry.h"

namespace dsa
{

/*!
 * @addtogroup TMap
 *
 * @{
 */

/*!
 * @brief 基于红黑树实现Map结构
 *
 */
template <
    typename K,
    typename V,
    typename CMP=dsa::Less<K> >
class MapRBT : public dsa::Dict<K,V>
{
public:
    typedef dsa::Entry<K,V,CMP> Pair;

private:
    RedBlackTree<Pair>  m_rb;

public:
    MapRBT() : m_rb() {};

    /** 获取根节点 */
    BinNodePtr<Pair>    root() {return this->m_rb.root();}
    /** 获取键值对数量 */
    int     size() const {return this->m_rb.size();}
    /** 插入键值对（若键存在，则覆盖Entry的value） */
    bool    put(K key, V val)
    {
        Pair pair(key, val);
        BinNodePtr<Pair> p = this->m_rb.insert(pair);
        p->data.value = val;
        return true;
    };
    /** 获取或修改键值对 */
    V*      get(K key)
    {
        BinNodePtr<Pair> p = this->m_rb.search(Pair(key));
        if (p)
            return &(p->data.value);
        else
            return nullptr;
    };
    /** 删除键值对 */
    bool    remove(K key) {return this->m_rb.remove(Pair(key));};
};

/*! @} */

} /* dsa */ 
#endif /* ifndef _MAP_RBT_H */
