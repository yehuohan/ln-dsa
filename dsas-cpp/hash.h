
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
#include "share/prime.h"
#include "share/compare.h"
#include "list.h"
#include "bitmap.h"
#include "hash_func.h"

namespace dsa
{

/*!
 * @addtogroup LHash
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
    virtual int     size() const = 0;
    virtual bool    put(K, V) = 0;
    virtual V*      get(K) = 0;
    virtual bool    remove(K) = 0;
};

#define HASH_PROBE_LINE     0x01
#define HASH_PROBE_QUAD     0x02
#define HASH_PROBE          HASH_PROBE_QUAD

/*!
 * @brief 散列表模板类
 *
 * <pre>
 * 装填因子： N/M = size/cap
 *
 * 冲突
 * (1): 使用链表
 * [*]
 * [*]-[*]
 * [*]-[*]-[*]
 * [*]
 * [*]-[*]
 * 每一个单元存储一个链表，冲突的单元属于同一个链表。
 * 使用链表可以解决任意冲突；
 * 但 空间分配不连续，系统缓存几乎失效。
 *
 * (2): 线性试探
 * [*][*][*][*][*][*][*][*]
 *  1  2  3
 * 当1号单元冲突，则试探2号，3号···，直至遇到空单元。
 * 试探的单元，就形成了一个线性试探的查找链。
 * 这样空间分配连续，可充分利用系统缓存；
 * 但 可能导致冲突增多。
 *
 * (3): 平方试探
 * 类似于线性试探，只是试探的距离用平方距离，即 1,4,9......
 * 当有冲突时，平方试探可以快速跳离冲突聚集的地方；
 * 但 平方试探不一定能试探所有的单元，会造成有些空单元利用不到。
 *
 * (4): 双向平方试探
 * 基于平方试控，不过试控距离变成 1, -1, 4, -4, 9, -9......
 * 散列容量取为 M = 4k+3 的素数，可以保证双平方试探的查找链的前 M 项均互异。
 *
 * </pre>
 *
 */
template <
    typename K,
    typename V,
    typename HF=dsa::Hash<K>,
    typename CMP=dsa::Less<K> >
class HashTable : public Dict<K, V>
{
private:
    dsa::Entry<K,V,CMP>** m_ht; /**< 散列容量数组，存放词条指针 */
    int     m_cap;          /**< 散列容量 */
    int     m_size;         /**< 实际插入的键值对元素 */
    dsa::Bitmap* lazy_rm;   /**< 懒惰删除标记，保证查找链不会中断 */
#define Is_Lazy_Removed(x)  (this->lazy_rm->test(x))
#define Mark_As_Removed(x)  (this->lazy_rm->set(x))
    HF      hash_func;      /**< 计算Hash的函数 */

protected:
    /** 沿查找链，查找是否已经存在key */
    inline int probe_hit(K key)
    {
#if HASH_PROBE == HASH_PROBE_LINE
        return probe_line_hit(key);
#elif HASH_PROBE == HASH_PROBE_QUAD
        return probe_quad_hit(key);
#endif
    }
    /** 沿查找链，查找可用空单元 */
    inline int probe_free(K key)
    {
#if HASH_PROBE == HASH_PROBE_LINE
        return probe_line_free(key);
#elif HASH_PROBE == HASH_PROBE_QUAD
        return probe_quad_free(key);
#endif
    }

    int probe_line_hit(const K&);
    int probe_line_free(const K&);
    int probe_quad_hit(const K&);
    int probe_quad_free(const K&);

    void init(int);
    void rehash();

public:
    HashTable(int n = 5) {this->init(n);}
    ~HashTable();

    /** 重载[]，仿问和修改已有词条，不能插入词条 */
    V& operator[] (const K key) {return this->m_ht[this->probe_hit(key)]->value;}
    /** 重载[]，仿问已有词条，不能插入词条 */
    const V& operator[] (const K key) const {return this->m_ht[this->probe_hit(key)]->value;}

    /** 获取键值对数量 */
    int     size() const {return this->m_size;}
    bool    put(K, V);
    V*      get(K);
    bool    remove(K);
};


/*!
 * @brief 散列表模板类
 *
 * 使用链表解决冲突。
 *
 */
template <
    typename K,
    typename V,
    typename HF=dsa::Hash<K>,
    typename CMP=dsa::Less<K> >
class HashTableList : public Dict<K, V>
{
private:
    dsa::List<dsa::Entry<K,V,CMP> >* m_ht; /**< 散列容量数组，存放词条指针 */
    int     m_cap;          /**< 散列容量 */
    int     m_size;         /**< 实际插入的键值对元素 */
    HF      hash_func;      /**< 计算Hash的函数 */

protected:
    /** 沿查找链，查找是否已经存在key */
    int probe_hit(K key);
    /** 沿查找链，查找可用空单元 */
    int probe_free(K key);

public:
    HashTableList(int n = 5);
    ~HashTableList();

    /** 获取键值对数量 */
    int     size() const {return this->m_size;}
    bool    put(K, V);
    V*      get(K);
    bool    remove(K);
};


/*! @} */


template <typename K, typename V, typename HF, typename CMP>
HashTable<K,V,HF,CMP>::~HashTable()
{
    for (int k = 0; k < this->m_cap; k ++)
    {
        if (this->m_ht[k])
            delete this->m_ht[k];
    }
    delete[] this->m_ht;
    delete this->lazy_rm;
}

/*!
 * @brief 创建散列表
 *
 * 这里使用dsa::prime_1048576来生成不小于n的素数。
 * 故创建散列表时，容量不应超过1048576，否则无法生成正确的素数。
 *
 * @param n: 散列表容量为 >= n 的素数
 * @return
 * @retval None
 */
template <typename K, typename V, typename HF, typename CMP>
void HashTable<K,V,HF,CMP>::init(int n)
{
#if HASH_PROBE == HASH_PROBE_LINE
    this->m_cap = dsa::prime_1048576(n);
#elif HASH_PROBE == HASH_PROBE_QUAD
    this->m_cap = dsa::prime_1048576_4k3(n);
#endif
    this->m_size = 0;
    this->m_ht = new dsa::Entry<K,V,CMP>*[this->m_cap];
    for (int k = 0; k < this->m_cap; k ++)
        this->m_ht[k] = nullptr;
    this->lazy_rm = new dsa::Bitmap(this->m_cap);
}

/*!
 * @brief 插入字典键-值对
 *
 * @param key: 待插入的键
 * @param val: 待插入的值
 * @return
 * @retval None
 */
template <typename K, typename V, typename HF, typename CMP>
bool HashTable<K,V,HF,CMP>::put(K key, V val)
{
    // 先检测key是否存在，若已存在key，则放弃插入key-val
    if (this->m_ht[this->probe_hit(key)])
        return false;
    // 试探出空单元，用于插入key-val
    uint index = this->probe_free(key);
    this->m_ht[index] = new Entry<K,V,CMP>(key, val);
    this->m_size ++;
    // 装填因子 >50% 时，重散列，保证恒有一定的空单元
    if (this->m_size * 2 > this->m_cap)
        this->rehash();
    return true;
}

/*!
 * @brief 根据键获取或修改值
 *
 * 在修改值前，需要判断返回的指针不为nullptr。
 *
 * @param key: 键
 * @return 返回对应key-value的指针，或nullptr
 * @retval None
 */
template <typename K, typename V, typename HF, typename CMP>
V* HashTable<K,V,HF,CMP>::get(K key)
{
    int index = this->probe_hit(key);
    // 若不存在key，则返回nullptr
    return this->m_ht[index] ? &(this->m_ht[index]->value) : nullptr;
}

/*!
 * @brief 根据键删除值
 *
 * @param key: 键
 * @return 返回删除成功与否的结果
 * @retval None
 */
template <typename K, typename V, typename HF, typename CMP>
bool HashTable<K,V,HF,CMP>::remove(K key)
{
    // 先检测key是否存在，若不存在key，则放弃删除
    int index = this->probe_hit(key);
    if (!this->m_ht[index])
        return false;
    // 删除key，并将单元置空，并添加懒惰删除标记
    delete this->m_ht[index];
    this->m_ht[index] = nullptr;
    this->m_size --;
    Mark_As_Removed(index);
    return true;
}

/*!
 * @brief 重散列
 *
 * <pre>
 * 重散列算法：装填因子过大时，采取“逐一取出再插入”的朴素策略，对单元数组扩容。
 * 不可简单地（通过memcpy()）将原单元数组复制到新单元数组，否则存在两个问题：
 * (1)会继承原有冲突；
 * (2)可能导致查找链在后端断裂，即便为所有扩单元设置懒惰删除标志也无济于事；
 * </pre>
 *
 * @param None
 * @return
 * @retval None
 */
template <typename K, typename V, typename HF, typename CMP>
void HashTable<K,V,HF,CMP>::rehash()
{
    int old_cap = this->m_cap;
    dsa::Entry<K,V,CMP>** old_ht = this->m_ht;
    // 重新初始化散列单元
    delete this->lazy_rm;
    this->init(2*old_cap);
    // 转移散列单元
    for (int k = 0; k < old_cap; k ++)
        if (old_ht[k]) this->put(old_ht[k]->key, old_ht[k]->value);
    // 释放原有散列单元
    for (int k = 0; k < old_cap; k ++)
        if (old_ht[k]) delete old_ht[k];
    delete[] old_ht;
}

/*!
 * @brief 线性试探，查看散列表是否已经存在key
 *
 * <pre>
 *
 * 无论散列表中是否已经存在key，均会返回一个下标r。
 * (1) 当 m_ht[r] == nullptr时，说明散列表没有以key为键的单元（一定没有懒惰删除标记）；
 * (2) 当 m_ht[r] != nullptr时，说明散列表已经有以key为键的单元（无论带有懒惰删除标记与否）；
 *
 * Lazy_Removed标记    空单元
 *         /           /
 * [a][b][#][c][d][e][ ]
 *  0  1  2  3  4  5  6
 * 查找'f'，则返回 r = 6，表示散列表中还没有'f'；
 * 查找'e'，则返回 r = 5，表示'e'已经存在于散列表中；
 *
 * </pre>
 *
 * @param key: 键
 * @return
 * @retval None
 */
template <typename K, typename V, typename HF, typename CMP>
int HashTable<K,V,HF,CMP>::probe_line_hit(const K& key)
{
    int r = this->hash_func(key) % this->m_cap;
    while((this->m_ht[r] && *(this->m_ht[r]) != key)    // 试探：跳过冲突的单元（优先跳过不为nullptr的单元）
        ||(!this->m_ht[r] && Is_Lazy_Removed(r)))       // 试探：跳过查找链上带懒惰删除标记的单元
    {
        r = (r + 1) % this->m_cap;
    }
    return r;
}

/*!
 * @brief 线性试探，查找空单元用于插入新元素
 *
 * @param key: 键
 * @return
 * @retval None
 */
template <typename K, typename V, typename HF, typename CMP>
int HashTable<K,V,HF,CMP>::probe_line_free(const K& key)
{
    int r = this->hash_func(key) % this->m_cap;
    while (this->m_ht[r])
        r = (r + 1) % this->m_cap;  // 线性试探，直到找到一个空单元（无论带有懒惰删除标记与否）
    return r;
}

/*!
 * @brief 平方试探，查看散列表是否已经存在key
 *
 * 试探距离： 1, -1, 2^2, -2^2, 3^2, -3^2......
 *
 * @param key: 键
 * @return
 * @retval None
 */
template <typename K, typename V, typename HF, typename CMP>
int HashTable<K,V,HF,CMP>::probe_quad_hit(const K& key)
{
    int i = this->hash_func(key) % this->m_cap;
    int r = i, s = 1;
    while((this->m_ht[r] && *(this->m_ht[r]) != key)    // 试探：跳过冲突的单元（优先跳过不为nullptr的单元）
        ||(!this->m_ht[r] && Is_Lazy_Removed(r)))       // 试探：跳过查找链上带懒惰删除标记的单元
    {
        if (s > 0)
            r = (i + s*s) % this->m_cap;
        else
            r = (i - s*s) % this->m_cap;
        s = (s > 0) ? -s : -(--s);
    }
    return r;
}

/*!
 * @brief 平方试探，查找空单元用于插入新元素
 *
 * @param key: 键
 * @return
 * @retval None
 */
template <typename K, typename V, typename HF, typename CMP>
int HashTable<K,V,HF,CMP>::probe_quad_free(const K& key)
{
    int i = this->hash_func(key) % this->m_cap;
    int r = i, s = 1;
    while (this->m_ht[r])
    {
        //平方试探，直到找到一个空单元（无论带有懒惰删除标记与否）
        if (s > 0)
            r = (i + s*s) % this->m_cap;
        else
            r = (i - s*s) % this->m_cap;
        s = (s > 0) ? -s : -(--s);
    }
    return r;
}


} /* dsa */

#endif /* ifndef _HASH_H */
