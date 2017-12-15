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

#include "share/swap.h"
//#include "pq_complete_heap.h"

namespace dsa
{

/*!
 * @addtogroup LVector
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
        this->m_array = new T[this->m_capacity];
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
        this->m_array = new T[this->m_capacity];
        for (int k = 0; k < this->m_size; k++)
        {
            this->m_array[k] = ele;
        }
    }

    /*!
     * @brief 拷贝构造函数
     *
     * @param rhs: 引用对象
     * @return
     * @retval None
     */
    Vector(const Vector<T>& V) {this->copy_from(V.m_array, 0, V.m_size );}

    ~Vector() { delete[] this->m_array; }

    // basic
    int     push_front(const T& ele);
    int     push_back(const T& ele);
    int     insert(int index, const T& ele);
    T       remove(int index);
    int     remove(int lo, int hi);
    void    clear(){this->m_size = 0;}
    bool    is_empty() const {return !bool(this->m_size);}
    unsigned int size() const {return this->m_size;}

    T& operator[](int index) {return this->m_array[index];}
    Vector<T>& operator=(const Vector<T>& V);

    // 查找find
    int     find(const T& ele) const {return this->find(ele, 0, this->m_size);};
    int     find(const T& ele, int lo, int hi) const;
    // 搜索search
    int     search(const T& ele) const {return this->search(ele, 0, this->m_size); };
    int     search(const T& ele, int lo, int hi) const {return this->bin_search(ele, lo, hi);};
    int     bin_search(const T& ele, int lo, int hi) const;
    int     fib_search(const T& ele, int lo, int hi) const;

    // 去重操作
    int     deduplicate();
    int     uniquify();

    // 排序sort
    void    bubble_sort(int lo, int hi);
    int     bubble(int lo, int hi);
    void    merge_sort(int lo, int hi);
    void    merge(int lo, int mi, int hi);
    void    quick_sort(int lo, int hi);
    int     partition(int lo, int hi);
    void    heap_sort(int lo, int hi);

protected:
    void    copy_from (const T* A, int lo, int hi );
    void    expand();

protected:
    unsigned int m_capacity;
    unsigned int m_size;
    T*  m_array;

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
    if(this->m_array) delete[] this->m_array;
    this->copy_from(V.m_array, 0, V.size());
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
    this->m_array = new T[this->m_capacity = 2*(hi-lo)];
    this->m_size = 0;
    while(lo < hi)
        this->m_array[this->m_size++] = A[lo++];
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
    this->m_array[this->m_size++] = ele;
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
        this->m_array[k] = this->m_array[k-1];
    }
    this->m_array[index] = ele;
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
    T ele = this->m_array[index];
    this->remove(index, index+1);
    return ele;

    /*
    for(int k = index; k < this->m_size - 1; k++)
    {
        this->m_array[k] = this->m_array[k+1];
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
    while(hi < this->m_size) this->m_array[lo++] = this->m_array[hi++];
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
    T* old_ar = this->m_array;         // save the old pointer to m_array
    this->m_capacity *= 2;
    this->m_array = new T[this->m_capacity];
    for(int k = 0; k < m_size; k++)
    {
        this->m_array[k] = old_ar[k];
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
    while((lo < hi--) && (ele != this->m_array[hi]));  // compare ele and m_array[hi] after hi--
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
        if (ele < this->m_array[mi]) hi = mi;
        else if (ele > this->m_array[mi]) lo = mi + 1;
        else return mi;
    }
    return -1;

#elif(0)
    while(1 < hi - lo)
    {
        // 2个分支判断，[lo, mi) or [mi, hi)
        int mi = (lo +hi)/2;
        ele < this->m_array[mi] ? hi = mi : lo = mi;
    }
    return (ele == this->m_array[lo] ? lo : -1);

#elif(1)
    while(lo < hi)
    {
        int mi = (lo + hi)/2;
        ele < this->m_array[mi] ? hi = mi : lo = mi + 1;
        // m_array[lo] <= ele all the time and
        // m_array[hi] > ele all the time
    }
    // 返回不大于ele的最大元素下标
    return --lo;

#else
    return ele < this->m_array[(hi+lo)/2] ?
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
        // 在前缀区间[0, k查找m_array[k]
        (this->find(this->m_array[k], 0, k) < 0) ?
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
        (this->m_array[k] == this->m_array[k+1]) ? this->remove(k+1) : k++;
    }
    return oldsize - this->m_size;

/* 高效版 */
#else
    int lo = 0, hi = 0;
    while(++hi < this->m_size)
    {
        // lo 一直指向已去重向量部分的最后一个元素
        // 相同元素通过 ++hi 跳过，实现覆盖去重
        if(this->m_array[lo] != this->m_array[hi])
            this->m_array[++lo] = this->m_array[hi];
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
        if(this->m_array[lo-1] > this->m_array[lo])
        {
            sorted = 0;
            // the max will be swaped to the position of hi
            T tmp = this->m_array[lo - 1];
            this->m_array[lo - 1] = this->m_array[lo];
            this->m_array[lo] = tmp;
        }
    }
    return sorted;

/* 改进版二 */
#else
    int last = lo;
    while(++lo < hi)
    {
        if(this->m_array[lo - 1] > this->m_array[lo])
        {
            // last是右侧已排好序区间的左侧下标
            last = lo;
            // the max will be swaped to the position of hi
            T tmp = this->m_array[lo - 1];
            this->m_array[lo - 1] = this->m_array[lo];
            this->m_array[lo] = tmp;
        }
    }
    return last;
#endif
}


/*!
 * @brief merge sort in [lo, hi) （归并排序）
 *
 * 排序范围为[lo, hi)
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

/*!
 * @brief 归并排序的归并操作
 *
 * @param lo,mi,hi 将[lo,mi)和[mi, hi)进行合并
 * @return
 * @retval None
 */
template <typename T>
void Vector<T>::merge(int lo, int mi, int hi)
{
    T* p = this->m_array + lo;
    int len = mi - lo;
    T* left = new T[len];
    for(int k = 0; k < len; k++)
        left[k] = p[k];
    T* right = this->m_array + mi;

    int i = 0, j = 0, k = 0;
    while(i < mi-lo && j < hi-mi)
    {
        if(left[i] <= right[j])
            p[k++] = left[i++];
        else
            p[k++] = right[j++];
    }
    while(i < mi - lo) p[k++] = left[i++];
    while(j < hi - mi) p[k++] = right[j++];
    delete[] left;
}


/*!
 * @brief 快速排序
 *
 * 排序范围为[lo, hi)
 *
 * @param lo : range index >= lo
 * @param hi : range index < hi
 * @return
 * @retval None
 */
template <typename T>
void Vector<T>::quick_sort(int lo, int hi)
{
    // 只有一个元素
    if (hi - lo < 2)
        return;
    int mi = this->partition(lo, hi-1);   // 构造轴点
    this->quick_sort(lo, mi);
    this->quick_sort(mi + 1, hi);
}

/*!
 * @brief 快速排序(quick_sort)轴点构造算法
 *
 * <pre>
 * 轴点可选取范围为[lo, hi]，与quick_sort的约定有所不同。
 * 轴点：左侧元素[lo, mi) <= 轴点元素mi <= 右侧元素(mi, hi]
 *
 * 根据轴点的确定过程，可知快速排序前后，可能打乱相同元素间的相对顺序。
 *
 * (1)基本形式
 * [p][    ][i     j][    ]
 *     ----           ----
 *      L              R
 * 比较候选轴点p和i和j，将i和j不断的归入到L或R中；
 *
 *
 * (2)变种形式
 * [p][      q][i       ][k----------]
 *    --------  --------
 *        L        R
 * 不断的比较候选轴点p和k
 * p < k : k归入R中；
 * p > k : k归入L中，即交换i和k，L的长度+1；
 * 最终交换p和q，q做为最终的轴点。
 *
 * </pre>
 *
 * @param lo : range index >= lo
 * @param hi : range index <= hi
 * @return
 * @retval None
 */
template <typename T>
int Vector<T>::partition(int lo, int hi)
{
#if(0)
    // 基本形式
    T pivot = this->m_array[lo];        // 候选轴点
    while(lo < hi)
    {
        while(lo < hi && this->m_array[hi] > pivot)
            hi--;
        this->m_array[lo] = this->m_array[hi];
        while(lo < hi && this->m_array[lo] < pivot)
            lo++;
        this->m_array[hi] = this->m_array[lo];
    }
    this->m_array[lo] = pivot;        // 最终轴点
    return lo;
#else
    // 变种形式
    T pivot = this->m_array[lo];
    int mi = lo;
    for (int k = lo + 1; k <= hi; k++)
    {
        if (this->m_array[k] < pivot)
        {
            mi ++;
            dsa::swap(this->m_array[k], this->m_array[mi]);
        }
    }
    dsa::swap(this->m_array[lo], this->m_array[mi]);
    return mi;
#endif
}


/*!
 * @brief 利用完全二叉堆对向量区间进行排序
 *
 * <pre>
 *
 * 元素移动示意图：
 *     max ------->
 *    /            \
 * [ # --- heap --- # --- sorted ---]
 *  lo             hi
 *
 * </pre>
 *
 * @param [lo, hi): 待排序区间
 * @return
 * @retval None
 */
template <typename T>
void Vector<T>::heap_sort(int lo, int hi)
{
    //PqComplHeap<T> h(this->m_array+lo, hi-lo);
    //while(!h.is_empty())
    //{
    //    // 将堆顶元素放入已经排序部分
    //    this->m_size[--hi] = h.del_max();
    //}
}

// namespace dsa end
}

#endif /* ifndef _VECTOR_H */
