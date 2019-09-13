
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

#ifndef DSAS_TRIE_TREE_H
#define DSAS_TRIE_TREE_H

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
 * @name TrieTree类型
 * @{
 */
struct TrieNode;
using TrieNodePtr = struct TrieNode*;
using TrieNodeData = dsa::MapRBT<char, TrieNodePtr>;
using TrieNodeIterator = TrieNodeData::Iterator;
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
        : parent(p), next(), word(w) {}

    /** 获取子节点数量 */
    int     size() const {return this->next.size();}
    /** 插入next节点 */
    void    put_next(char key, TrieNodePtr val) {this->next.put(key, val);}
    /** 获取next节点 */
    TrieNodePtr get_next(char key)
    {
        TrieNodePtr* p = this->next.get(key);
        return (p) ? (*p) : nullptr;
    }
    /** 迭代起点 */
    TrieNodeIterator    begin() {return this->next.begin();}
    /** 迭代结束 */
    TrieNodeIterator    end() {return this->next.end();}
};

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

    static void free_data(TrieNodeData::Pair& td);

public:
    TrieTree() : m_root(new TrieNode()), m_size(0) {}
    ~TrieTree()
    {
        if (this->m_root->size())
            this->m_root->next.traverse(free_data);
        else
            delete this->m_root;
    }

    int     size() const {return this->m_size;}
    bool    insert(const dsa::String& word);
    bool    remove(const dsa::String& word);
    bool    contains(const dsa::String& word);
    bool    is_prefix(const dsa::String& prefix);
    template <typename VST> void traverse(VST& visit);
};

/*! @} */

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
void TrieTree::free_data(TrieNodeData::Pair& td)
{
    if (td.value->size())
        td.value->next.traverse(TrieTree::free_data);
    else
    {
        delete td.value;
        td.value = nullptr;
    }
}

/*!
 * @brief 添加word到字典树中。
 *
 * @param None
 * @return
 * @retval 字典树若原本不含word，返回true，否则返回false
 */
bool TrieTree::insert(const dsa::String& word)
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
        return true;
    }
    return false;
}

/*!
 * @brief 删除字典树中的word。
 *
 * @param None
 * @return
 * @retval 字典树含有word，返回true，否则返回false
 */
bool TrieTree::remove(const dsa::String& word)
{
    // TODO: 删除一个word
    return true;
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

/*!
 * @brief 遍历字典树的所有word
 *
 * @param visit: 访问word的函数
 * @return
 * @retval None
 */
template <typename VST>
void TrieTree::traverse(VST& visit)
{
    // TODO: 单词遍历
#if 0
    if (!this->m_root->size())
        return;
    TrieNodePtr node;
    TrieNodeIterator iter;
    dsa::Stack<TrieNodeIterator> s;
    dsa::String w;

    node = this->m_root;
    iter = node->begin();
    s.push(iter);
    while (!s.is_empty())
    {
        w.push((*iter).key);
        if ((*iter).value->word)
            visit(w);
        if ((*iter).value->size())
        {
            node = (*iter).value;
            s.push(iter);
            iter = (*iter).value->begin();
        }
        else
        {
            w.pop();
            if (++iter == node->end())
                iter = s.pop();
        }
    }
#endif
}

} /* dsa */

#endif /* ifndef DSAS_TRIE_TREE_H */
