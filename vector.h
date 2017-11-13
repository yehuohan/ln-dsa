//==============================================================================
/*!
 * @file vector.h
 * @brief Vector struct
 *
 * Vector implementation with some basic functions and advanced
 * functions such as find, search, sort and so on.
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _VECTOR_H
#define _VECTOR_H

namespace dsa
{

/*!
 * @addtogroup Linear
 *
 * @{
 */

#define CAPACITY    50

template <typename T>
class Vector
{
public:
    /*!
     * @brief Vector构造函数
     *
     * @param None
     * @return
     * @retval None
     */
    Vector()
    {
        this->m_size = 0;
        this->m_capacity = CAPACITY;
        this->m_ar = new T[this->m_capacity];
    }

    /*!
     * @brief Vector构造函数
     * 初始化数据内容均为ele
     * @param None
     * @return
     * @retval None
     */
    Vector(int size, int capacity, const T& ele)
    {
        this->m_size = size;
        this->m_capacity = capacity;
        this->m_ar = new T[this->m_capacity];
        for (int k = 0; k < this->m_size; k++)
        {
            this->m_ar[k] = ele;
        }
    }

    /*!
     * @brief 拷贝构造函数
     *
     * @param rhs: 引用对象
     * @return
     * @retval None
     */
    Vector(const Vector<T>& V) {this->copy_from(V.m_ar, 0, V.m_size );}

    ~Vector() { delete[] this->m_ar; }

    // basic
    int     push_front(const T& ele);
    int     push_back(const T& ele);
    int     insert(int index, const T& ele);
    T       remove(int index);
    int     remove(int lo, int hi);
    void    clear(){this->m_size = 0;}
    bool    is_empty() const {return !bool(this->m_size);}
    unsigned int size() const {return this->m_size;}

    T& operator[](int index) const {return  this->m_ar[index];}
    Vector<T>& operator=(const Vector<T>& V);

    // find
    int     find(const T& ele) const {return this->find(ele, 0, this->m_size);};
    int     find(const T& ele, int lo, int hi) const;
    // search
    int     search(const T& ele) const {return this->search(ele, 0, this->m_size); };
    int     search(const T& ele, int lo, int hi) const {return this->bin_search(ele, lo, hi);};
    int     bin_search(const T& ele, int lo, int hi) const;
    int     fib_search(const T& ele, int lo, int hi) const;

    // deduplicate
    int     deduplicate();
    // uniquify
    int     uniquify();

    // sort
    void    bubble_sort(int lo, int hi);
    int     bubble(int lo, int hi);
    void    merge_sort(int lo, int hi);
    void    merge(int lo, int mi, int hi);

protected:
    void    copy_from (const T* A, int lo, int hi );
    void    expand();

private:
    unsigned int m_capacity;
    unsigned int m_size;
    T*  m_ar;

};


/*! @} */


/*!
 * @brief overload operator =
 *
 * @param V: the value to set by operator =
 * @return reference of this vector
 * @retval None
 */
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& V)
{
    if(this->m_ar) delete[] this->m_ar;
    this->copy_from(V.m_ar, 0, V.size());
    return *this;
}

/*!
 * @brief copy from another vector
 *
 * @param A: vector copying from
 * @param lo,hi: copying range
 * @return
 * @retval None
 */
template <typename T>
void Vector<T>::copy_from(T const* A, int lo, int hi )
{
    this->m_ar = new T[this->m_capacity = 2*(hi-lo)];
    this->m_size = 0;
    while(lo < hi)
        this->m_ar[this->m_size++] = A[lo++];
}

/*!
 * @brief insert element to the front(first) position.
 *
 * @param ele: the element to be insert
 * @return
 * @retval None
 */
template <typename T>
inline int Vector<T>::push_front(const T& ele)
{
    this->insert(0, ele);
}

/*!
 * @brief insert element from the back of vector
 *
 * @param ele: the element to be insert
 * @return index of inserted element
 * @retval None
 */
template <typename T>
int Vector<T>::push_back(const T& ele)
{
    if(this->m_size >= this->m_capacity)
    {
        this->expand();
    }
    this->m_ar[this->m_size++] = ele;
    return this->m_size-1;
}

/*!
 * @brief insert element
 *
 * insert element in index, meaning that [index] = element
 *
 * @param index: where to insert
 * @param ele: the element to insert
 * @return index of inserted element
 * @retval None
 */
template <typename T>
int Vector<T>::insert(int index, const T& ele)
{
    if(this->m_size >= this->m_capacity)
    {
        this->expand();
    }
    for(int k = this->m_size; k > index; k--)
    {
        this->m_ar[k] = this->m_ar[k-1];
    }
    this->m_ar[index] = ele;
    this->m_size++;
    return index;
}

/*!
 * @brief remove element in index
 *
 * @param index : index of element to be removed
 * @return the value had been removed
 * @retval None
 */
template <typename T>
T Vector<T>::remove(int index)
{
    // delete interval (r, r+1) to delelte single element
    T ele = this->m_ar[index];
    this->remove(index, index+1);
    return ele;

    /*
    for(int k = index; k < this->m_size - 1; k++)
    {
        this->m_ar[k] = this->m_ar[k+1];
    }
    this->m_size--;
    */
}

/*!
 * @brief delete interval [lo, hi)
 *
 * @param lo : range index >= lo
 * @param hi : range index < hi
 * @return the number of element been removed
 * @retval None
 */
template <typename T>
int Vector<T>::remove(int lo, int hi)
{
    if(lo == hi) return 0;
    while(hi < this->m_size) this->m_ar[lo++] = this->m_ar[hi++];
    this->m_size = lo;
    return hi-lo;
}

/*!
 * @brief expand vector capacity
 *
 * @param None
 * @return
 * @retval None
 */
template <typename T>
void Vector<T>::expand()
{
    T* old_ar = this->m_ar;         // save the old pointer to m_ar
    this->m_capacity *= 2;
    this->m_ar = new T[this->m_capacity];
    for(int k = 0; k < m_size; k++)
    {
        this->m_ar[k] = old_ar[k];
    }
    delete[] old_ar;
}

/*!
 * @brief find ele in [lo, hi)
 *
 * @param ele : what element to search
 * @param lo : range index >= lo
 * @param hi : range index < hi
 * @return index of the ele found or -1 when ele is not found
 * @retval None
 */
template <typename T>
int Vector<T>::find(const T& ele, int lo, int hi) const
{
    while((lo < hi--) && (ele != this->m_ar[hi]));  // compare ele and m_ar[hi] after hi--
    return hi;
}

/*!
 * @brief binary search in [lo, hi)
 *
 * @param ele : what element to search
 * @param lo : range index >= lo
 * @param hi : range index < hi
 * @return index of the element that <= ele
 * @retval None
 */
template <typename T>
int Vector<T>::bin_search(const T& ele, int lo, int hi) const
{
    // iteration
#if(0)
    while(lo < hi)
    {
        // 3个分支判断，[lo, mi) or (mi, hi) or mi
        int mi = (lo + hi)/2;
        if (ele < this->m_ar[mi]) hi = mi;
        else if (ele > this->m_ar[mi]) lo = mi + 1;
        else return mi;
    }
    return -1;

#elif(0)
    while(1 < hi - lo)
    {
        // 2个分支判断，[lo, mi) or [mi, hi)
        int mi = (lo +hi)/2;
        ele < this->m_ar[mi] ? hi = mi : lo = mi;
    }
    return (ele == this->m_ar[lo] ? lo : -1);

#elif(1)
    while(lo < hi)
    {
        int mi = (lo + hi)/2;
        ele < this->m_ar[mi] ? hi = mi : lo = mi + 1;
        // m_ar[lo] <= ele all the time and
        // m_ar[hi] > ele all the time
    }
    // 返回不大于ele的最大元素下标
    return --lo;

#else

    return ele < this->m_ar[(hi+lo)/2] ?
        bin_search(ele, lo, (hi+lo)/2)
        : bin_search(ele, (hi+lo)/2, hi);
    return 0;
#endif
}

/*!
 * @brief fibonacci search in [lo, hi)
 *
 * @param ele : what element to search
 * @param lo : range index >= lo
 * @param hi : range index < hi
 * @return
 * @retval None
 */
template <typename T>
int Vector<T>::fib_search(const T& ele, int lo, int hi) const
{
    return 0;
}

/*!
 * @brief 无序向量去重
 *
 * @param None
 * @return
 * @retval None
 */
template <typename T>
int Vector<T>::deduplicate()
{
    int oldsize = this->m_size;
    int k = 1;
    while(k < this->m_size)
    {
        // 在前缀区间[0, k查找m_ar[k]
        (this->find(this->m_ar[k], 0, k) < 0) ?
            k ++
            : this->remove(k);
    }
    return oldsize - this->m_size;
}

/*!
 * @brief 有序向量去重
 *
 * @param None
 * @return
 * @retval None
 */
template <typename T>
int Vector<T>::uniquify()
{
/* 低效版 */
#if(0)
    int oldsize = this->m_size;
    int k = 0;
    while(k < this->m_size-1)
    {
        // 对于有序向量，连续remove多个相同的element时，有大量的重复移动
        (this->m_ar[k] == this->m_ar[k+1]) ? this->remove(k+1) : k++;
    }
    return oldsize - this->m_size;

/* 高效版 */
#else
    int lo = 0, hi = 0;
    while(++hi < this->m_size)
    {
        // lo 一直指向已去重向量部分的最后一个元素
        // 相同元素通过 ++hi 跳过，实现覆盖去重
        if(this->m_ar[lo] != this->m_ar[hi])
            this->m_ar[++lo] = this->m_ar[hi];
    }
    this->m_size = ++lo;
    return hi-lo;

#endif
}

/*!
 * @brief bubble sort between [lo, hi)(冒泡排序改进版)
 *
 * @param lo : range index >= lo
 * @param hi : range index < hi
 * @return
 * @retval None
 */
template <typename T>
void Vector<T>::bubble_sort(int lo, int hi)
{
#if(0)
    while(!this->bubble(lo, hi--));
#else
    while(lo < (hi = this->bubble(lo, hi)));
#endif
}
template <typename T>
int Vector<T>::bubble(int lo, int hi)
{
/* 改进版一 */
#if(0)
    // stop continue sorting if [lo, hi] was sorted
    int sorted = 1;
    while(++lo < hi)
    {
        if(this->m_ar[lo-1] > this->m_ar[lo])
        {
            sorted = 0;
            // the max will be swaped to the position of hi
            T tmp = this->m_ar[lo - 1];
            this->m_ar[lo - 1] = this->m_ar[lo];
            this->m_ar[lo] = tmp;
        }
    }
    return sorted;

/* 改进版二 */
#else
    int last = lo;
    while(++lo < hi)
    {
        if(this->m_ar[lo - 1] > this->m_ar[lo])
        {
            // last是右侧已排好序区间的左侧下标
            last = lo;
            // the max will be swaped to the position of hi
            T tmp = this->m_ar[lo - 1];
            this->m_ar[lo - 1] = this->m_ar[lo];
            this->m_ar[lo] = tmp;
        }
    }
    return last;
#endif
}

/*!
 * @brief merge sort in [lo, hi) （归并排序）
 *
 * @param lo : range index >= lo
 * @param hi : range index < hi
 * @return
 * @retval None
 */
template <typename T>
void Vector<T>::merge_sort(int lo, int hi)
{
    if(hi - lo < 2) return;
    int mi = (lo + hi) / 2;
    merge_sort(lo, mi);
    merge_sort(mi, hi);
    merge(lo, mi, hi);
}
template <typename T>
void Vector<T>::merge(int lo, int mi, int hi)
{
    /* merge [lo, mi) and [mi, hi) */
    T* p = this->m_ar + lo;
    int len = mi - lo;
    T* left = new T[len];
    for(int k = 0; k < len; k++)
    {
        *(left + k) = *(p + k);
    }
    T* right = this->m_ar + mi;

    int i = 0, j = 0, k = 0;
    while(i < mi-lo && j < hi-mi)
    {
        if(left[i] <= right[j])
        {
            p[k++] = left[i++];
        }
        else
        {
            p[k++] = right[j++];
        }
    }
    while(i < mi -lo)
    {
        p[k++] = left[i++];
    }
    while(j < hi - mi)
    {
        p[k++] = right[j++];
    }
    delete[] left;
}

// namespace dsa end
}

#endif /* ifndef _VECTOR_H */
