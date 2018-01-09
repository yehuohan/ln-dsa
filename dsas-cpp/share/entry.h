//==============================================================================
/*!
 * @file entry.h
 * @brief 词条类
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================


#ifndef DSAS_ENTRY_H
#define DSAS_ENTRY_H 

namespace dsa
{

/*!
 * @addtogroup Share
 *
 * @{
 */

/*!
 * @brief 词条类，实现元素的比较
 *
 * 键至少实现了 '<' 运算符
 *
 */
template <typename K, typename V>
struct Entry
{
    K key;
    V value;

    Entry(K _key = K(), V _value = V()) : key(_key), value(_value) {}
    Entry(const Entry<K,V>& e): key(e.key), value(e.value) {}

    bool operator<  (const Entry<K,V>& e) const {return this->key < e.key;}
    bool operator>  (const Entry<K,V>& e) const {return e.key < this->key;}
    bool operator== (const Entry<K,V>& e) const {return !(this->key < e.key || e.key < this->key);}
    bool operator!= (const Entry<K,V>& e) const {return  (this->key < e.key || e.key < this->key);}
    bool operator<= (const Entry<K,V>& e) const {return (*this < e || *this == e);}
    bool operator>= (const Entry<K,V>& e) const {return (*this > e || *this == e);}
};

/*! @} */

} /* dsa */ 
#endif /* ifndef DSAS_ENTRY_H */

