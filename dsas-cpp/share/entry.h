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

#include "compare.h"

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
 * <pre>
 *
 * 作为Hash的单元节点，相对完整的实现了比较运算符，赋值运算符，拷贝构造函数。
 * 其中，通过比较函数CMP，实现比较运算符<,>,==,!=,>=,<=。
 *
 * </pre>
 *
 */
template <typename K, typename V, typename CMP = dsa::Less<K> >
struct Entry
{
    K   key;        /**< 键 */
    V   value;      /**< 值 */
    CMP cmp;        /**< 比较函数 */

    Entry(K _key = K(), V _value = V()) : key(_key), value(_value) {}
    Entry(const Entry<K,V,CMP>& e): key(e.key), value(e.value) {}

    /** 重载= */
    Entry<K,V,CMP>& operator= (const Entry<K,V,CMP>& e) {key = e.key; value = e.value; return *this;}

    /*!
     * @name 实现Entry之间的比较
     * @{
     */
    bool operator<  (const Entry<K,V,CMP>& e) const {return cmp(key, e.key);}
    bool operator>  (const Entry<K,V,CMP>& e) const {return cmp(e.key, key);}
    bool operator== (const Entry<K,V,CMP>& e) const {return !(cmp(key, e.key) || cmp(e.key, key));}
    bool operator!= (const Entry<K,V,CMP>& e) const {return  (cmp(key, e.key) || cmp(e.key, key));}
    bool operator<= (const Entry<K,V,CMP>& e) const {return (*this < e || *this == e);}
    bool operator>= (const Entry<K,V,CMP>& e) const {return (*this > e || *this == e);}
    /*! @} */

    /*!
     * @name 实现Entry与key之间的比较
     * @{
     */
    bool operator<  (const K& e) const {return cmp(key, e);}
    bool operator>  (const K& e) const {return cmp(e, key);}
    bool operator== (const K& e) const {return !(cmp(key, e) || cmp(e, key));}
    bool operator!= (const K& e) const {return  (cmp(key, e) || cmp(e, key));}
    bool operator<= (const K& e) const {return (*this < e || *this == e);}
    bool operator>= (const K& e) const {return (*this > e || *this == e);}
    /*! @} */
};

/*! @} */

} /* dsa */ 
#endif /* ifndef DSAS_ENTRY_H */

