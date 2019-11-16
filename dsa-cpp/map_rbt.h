
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

#ifndef DSAS_MAP_RBT_H
#define DSAS_MAP_RBT_H

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
template <typename K, typename V, typename CMP = dsa::Less<K>>
class MapRBT : public dsa::Dict<K,V>
{
public:
    using Pair = dsa::Entry<K,V,CMP>;
    using Iterator = typename dsa::BinTree<Pair>::Iterator;

private:
    RedBlackTree<Pair>  m_rb;

public:
    MapRBT() : m_rb() {};

    /** 迭代起点 */
    Iterator    begin() {return this->m_rb.begin();};
    /** 迭代结束 */
    Iterator    end() {return this->m_rb.end();}
    /** 遍历Map键值对 */
    template <typename VST> void traverse(VST& visit, dsa::TraverseType type = DLR)
    {
        this->m_rb.root()->traverse(visit, type);
    }
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
#endif /* ifndef DSAS_MAP_RBT_H */
