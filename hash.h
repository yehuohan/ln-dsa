
//==============================================================================
/*!
 * @file hash.h
 * @brief 散列结构
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _HASH_H
#define _HASH_H

#include "share/entry.h"

namespace dsa
{

/*!
 * @addtogroup Hash
 *
 * @{
 */

/*!
 * @brief 字典接口类
 *
 */
template <typename K, typename V>
struct Dict
{
    virtual int size() const = 0;
    virtual bool put(K, V) = 0;
    virtual V* get(K) = 0;
    virtual bool remove(K) = 0;
};


/*!
 * @brief 散列表模板类
 *
 * 装填因子： N/M
 *
 */
template <typename K, typename V>
class HashTable : public Dict<K, V>
{
private:
    Entry<K,V>** ht;    /**< 散列容量数组，存放词条指针 */
    int m_M;            /**< 散列容量 */
    int m_N;            /**< 实际插入的键值对元素 */

public:
    HashTable(int c = 5);
    ~HashTable();

    /*!
     * @brief 获取键值对数量
     *
     */
    int size() const {return m_N;}
    bool put(K, V);
    V* get(K);
    bool remove(K);
};

/*! @} */


/*!
 * @brief 创建散列表
 *
 * @param c: 散列表的大小为 >= c 素数
 * @return
 * @retval None
 */
template <typename K, typename V>
HashTable<K,V>::HashTable(int c)
{
    this->m_N = 0;
}

template <typename K, typename V>
HashTable<K,V>::~HashTable()
{

}

/*!
 * @brief 插入字典键-值对
 *
 * @param key 待插入的键
 * @param val 待插入的值
 * @return
 * @retval None
 */
template <typename K, typename V>
bool HashTable<K,V>::put(K key, V val)
{

}

/*!
 * @brief 根据键获取值
 *
 * @param key 键
 * @return
 * @retval None
 */
template <typename K, typename V>
V* HashTable<K,V>::get(K key)
{

}

/*!
 * @brief 根据键删除值
 *
 * @param key 键
 * @return 返回删除成功与否的结果
 * @retval None
 */
template <typename K, typename V>
bool HashTable<K,V>::remove(K key)
{

}


} /* dsa */

#endif /* ifndef _HASH_H */
