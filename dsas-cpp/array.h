//==============================================================================
/*!
 * @file array.h
 * @brief 数组实现
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _ARRAY_H
#define _ARRAY_H

#include "vector.h"

namespace dsa
{

/*!
 * @addtogroup LArray
 *
 * @{
 */

/*!
 * @brief 数组类
 *
 */
template <typename T, int N>
class Array
{
protected:
    int     m_cap;              /** 容量 */
    T*      m_array;            /** 存放数据的数组 */

public:
    Array() : m_cap(N) {this->m_array = new T[this->m_cap];}
    Array(const dsa::Vector<T>& V) : m_cap(N)
    {
        this->m_array = new T[this->m_cap];
        for (int k = 0; k < this->m_cap; k ++)
            this->m_array[k] = V[k];
    }
    Array(const Array<T,N>& A)
    {
        this->m_cap = A.m_cap;
        this->m_array = new T[this->m_cap];
        for (int k = 0; k < this->m_cap; k ++)
            this->m_array[k] = A.m_array[k];
    }
    ~Array() {delete[] this->m_array;}

    /** 返回数组容量 */
    int     max_size() const {return this->m_cap;}
    /** 返回数组地址 */
    T*      data() {return this->m_array;}
    /** 访问指定下标元素 */
    T&      at(int index)
    {
        if (0<=index && index<this->m_cap)
            return this->m_array[index];
        throw "array: out of range";
    }
    /** 填充数据 */
    void    fill(const T& ele) {for (int k = 0; k < this->m_cap; k ++) this->m_array[k] = ele;}

    /** 重载[]，可以修改m_array[index] */
    T& operator[](int index) {return this->m_array[index];}
    /** 重载[]，用于const Vector下标访问，不能修改m_array[index] */
    const T& operator[](int index) const {return this->m_array[index];}
    /** 重载= */
    Array<T,N>& operator=(const Array<T,N>& A)
    {
        delete[] this->m_array;
        this->m_cap = A.m_cap;
        this->m_array = new T[this->m_cap];
        for (int k = 0; k < this->m_cap; k ++)
            this->m_array[k] = A.m_array[k];
    }

    /** 在整个Array中查找 */
    int     find(const T& ele) const {return this->find(ele, 0, this->m_cap);}
    /** 在[lo, hi)查找特定元素；若找到ele，则返回下标，否则返回-1 */
    int     find(const T& ele, int lo, int hi) const
    {
        while((lo < hi--) && (ele != this->m_array[hi]));
        return hi;
    }
};

/*! @} */
} /* dsa */

#endif /* ifndef _ARRAY_H */
