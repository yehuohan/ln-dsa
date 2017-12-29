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
 */
template <typename K, typename V>
struct Entry
{
    K key;
    V value;

    Entry(K _key = K(), V _value = V()) : key(_key), value(_value) {}
    Entry(const Entry<K,V>& e): key(e.key), value(e.value) {}

    bool operator< (const Entry<K,V>& e) const {return key < e.key;}
    bool operator> (const Entry<K,V>& e) const {return key > e.key;}
    bool operator== (const Entry<K,V>& e) const {return key == e.key;}
    bool operator!= (const Entry<K,V>& e) const {return key != e.key;}
};

/*! @} */

} /* dsa */ 
#endif /* ifndef DSAS_ENTRY_H */

