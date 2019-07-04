
//==============================================================================
/*!
 * @file trie_node.h
 * @brief trie node of trie tree.
 *
 * @date 2019-07-03
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _TRIE_NODE_H
#define _TRIE_NODE_H

#include "map_rbt.h"

namespace dsa
{

/*!
 * @addtogroup TTrieTree
 *
 * @{
 */

struct TrieNode;

/*!
 * @name TrieTree类型
 * @{
 */
using TrieNodePtr = struct TrieNode*;
using TrieNodeData = dsa::MapRBT<char, TrieNodePtr>;
/*! @} */

/*!
 * @brief
 *
 * Trie Tree(字典树)节点，使用Map存储节点，用key作为路径字母，value指向下一节点。
 *
 */
struct TrieNode
{
    TrieNodePtr     parent;         /**< 父节点 */
    TrieNodeData    next;           /**< 节点数据 */
    bool            word;           /**< 单词尾节点标志 */

    TrieNode(TrieNodePtr p = nullptr,
            bool w = false)
        : parent(p) , next() , word(w) {}

    /** 插入next节点 */
    void put_next(char key, TrieNodePtr val) {this->next.put(key, val);}
    /** 获取next节点 */
    TrieNodePtr get_next(char key)
    {
        TrieNodePtr* p = this->next.get(key);
        return (p) ? (*p) : nullptr;
    }
};


/*! @} */

} /* dsa */

#endif /* ifndef _TRIE_NODE_H */
