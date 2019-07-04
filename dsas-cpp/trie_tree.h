
//==============================================================================
/*!
 * @file trie_tree.h
 * @brief trie_tree implementation.
 *
 * @date 2019-07-03
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _TRIE_TREE_H
#define _TRIE_TREE_H

#include "trie_node.h"
#include "map_rbt.h"
#include "string.h"
#include "queue.h"

namespace dsa
{

/*!
 * @addtogroup TTrieTree
 *
 * @{
 */

/*!
 * @brief
 *
 * <pre>
 * Trie Tree(字典树)实现。
 *
 *  含有{he, she, his, hers}字典树如下：
 *
 *          0(root)  <1,h> <3,s>
 *         /     \
 *        1h      3s
 *      /   \     |
 *      2e  6i    4h
 *      |   |     |
 *      8r  7s    5e
 *      |
 *      9s
 *
 *  根节点为root，其中用MapRBT保存着子节点1和3的指针。
 *  节点2,5,7,9为一个word的尾节点。
 *  对节点内存释放理解，以节点8和节点9为例：
 *      在节点8的next保存着节点9的指针，而节点9的next没有子节点了，
 *      所以节点8的next中指向节点的9的指针可以delete。
 *
 * </pre>
 *
 */
class TrieTree
{
protected:
    TrieNodePtr     m_root;
    int             m_size;

    static void remove_at(TrieNodeData::Pair& td);

public:
    TrieTree() : m_root(new TrieNode()), m_size(0) {}
    ~TrieTree()
    {
        if (m_root)
            this->remove(this->m_root);
    }

    int     size() const {return this->m_size;}
    void    insert(const dsa::String& word);
    void    remove(TrieNodePtr root);
    bool    contains(const dsa::String& word);
    bool    is_prefix(const dsa::String& prefix);
};

/*! @} */

/*!
 * @brief 添加word到字典树中。
 *
 * @param None
 * @return
 * @retval None
 */
void TrieTree::insert(const dsa::String& word)
{
    TrieNodePtr node = this->m_root;
    for (int k = 0; k < word.size(); k ++)
    {
        char ch = word[k];
        if (!node->get_next(ch))
            node->put_next(ch, new TrieNode(node, false));
        node = node->get_next(ch);
    }
    // 没有该单词时，m_size才增加
    if (!node->word)
    {
        node->word = true;
        this->m_size ++;
    }
}

/*!
 * @brief 释放TrieNodeData::Pair中的value内存
 *
 * TrieNodeData是使用一个MapRBT类型，本质是红黑树结构，其节点TrieNodeData::Pair为键值对为Entry<key, TrieNodePtr>。
 * 其中的TrieNodePtr值由TrieTree申请和释放，而TrieNodeData::Pair由红黑树释放（最终在BinTree释放）。
 *
 * @param None
 * @return
 * @retval None
 */
void TrieTree::remove_at(TrieNodeData::Pair& td)
{
    if (td.value->next.size())
        td.value->next.traverse(TrieTree::remove_at);
    else
    {
        delete td.value;
        td.value = nullptr;
    }
}

/*!
 * @brief 移除以node为根节点的子树。
 *
 * @param None
 * @return
 * @retval None
 */
void TrieTree::remove(TrieNodePtr node)
{
    if (node->next.size())
        node->next.traverse(remove_at);
    else
        delete node;
}

/*!
 * @brief 判断字典树是否包含word
 *
 * @param None
 * @return
 * @retval None
 */
bool TrieTree::contains(const dsa::String& word)
{
    TrieNodePtr node = this->m_root;
    for (int k = 0; k < word.size(); k ++)
    {
        char ch = word[k];
        if (node->get_next(ch))
            node = node->get_next(ch);
        else
            return false;
    }
    return node->word;
}

/*!
 * @brief 判断字典树中是否含有前缀prefix
 *
 * @param None
 * @return
 * @retval None
 */
bool TrieTree::is_prefix(const dsa::String& prefix)
{
    TrieNodePtr node = this->m_root;
    for (int k = 0; k < prefix.size(); k ++)
    {
        char ch = prefix[k];
        if (node->get_next(ch))
            node = node->get_next(ch);
        else
            return false;
    }
    return true;
}

} /* dsa */

#endif /* ifndef _TRIE_TREE_H */
