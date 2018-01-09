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
#include "share/rand.h"

namespace dsa
{

/*!
 * @addtogroup LVector
 *
 * @{
 */

#define VECTOR_CAPACITY    50

template <typename T>
class Vector
{
public:
    Vector(int capacity = VECTOR_CAPACITY) : m_size(0), m_capacity(capacity) {this->m_array = new T[this->m_capacity];}
    Vector(int size, int capacity, const T& ele);
    Vector(const T* A, int n ) {this->copy_from(A, 0, n);}
    Vector(const T* A, int lo, int hi ) {this->copy_from( A, lo, hi);}
    Vector(const Vector<T>& V);
    Vector(const Vector<T>& V, int lo, int hi );
    ~Vector() {delete[] this->m_array;}

    /** 清空数据 */
    void    clear() {this->m_size = 0;}
    /** 判断是否为空 */
    bool    is_empty() const {return !bool(this->m_size);}
    /** 返回元素数量 */
    int     size() const {return this->m_size;}
    int     push_front(const T& ele);
    int     push_back(const T& ele);
    int     insert(int index, const T& ele);
    T       remove(int index);
    int     remove(int lo, int hi);

    /** 下标索引重写 */
    T& operator[](int index) const {return this->m_array[index];}
    Vector<T>& operator=(const Vector<T>& V);

    /** 在整个Vector中查找 */
    int     find(const T& ele) const {return this->find(ele, 0, this->m_size);};
    int     find(const T& ele, int lo, int hi) const;
    /** 在整个Vector中搜索 */
    int     search(const T& ele) const {return this->search(ele, 0, this->m_size); };
    /** 在区间内搜索 */
    int     search(const T& ele, int lo, int hi) const {return this->bin_search(ele, lo, hi);};
    int     bin_search(const T& ele, int lo, int hi) const;
    int     fib_search(const T& ele, int lo, int hi) const;

    int     deduplicate();
    int     uniquify();

    /** 打乱整个Vector的顺序 */
    void    unsort() {this->unsort(0, this->m_size);}
    void    unsort(int lo, int hi);

    /** 返回Vector的最大元素下标 */
    int     select_max() {this->select_max(0, this->m_size);}
    int     select_max(int lo, int hi);

    /** 对所有Vector元素排序 */
    void    sort() {this->quick_sort(0, this->m_size);}
    void    bubble_sort(int lo, int hi);
    int     bubble(int lo, int hi);
    void    merge_sort(int lo, int hi);
    void    merge(int lo, int mi, int hi);
    void    selection_sort(int lo, int hi);
    void    insertion_sort(int lo, int hi);
    void    quick_sort(int lo, int hi);
    int     partition(int lo, int hi);
    void    shell_sort(int lo, int hi);
    void    shell_insertion(int w, int lo, int hi);

    template <typename VST> void traverse(VST& visit);

protected:
    void    copy_from (const T* A, int lo, int hi );
    void    expand();

protected:
    int m_capacity;
    int m_size;
    T*  m_array;

};

/*! @} */


/*!
 * @brief Vector构造函数
 *
 * 初始化数据内容均为ele
 *
 * @param None
 * @return
 * @retval None
 */
template <typename T>
Vector<T>::Vector(int size, int capacity, const T& ele)
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
 * 拷贝构造函数是即类实例化的过程，故不能执行delete[] m_array。
 *
 * @param None
 * @return
 * @retval None
 */
template <typename T>
Vector<T>::Vector(const Vector<T>& V)
{
    this->copy_from(V.m_array, 0, V.m_size );
}

/*!
 * @brief 拷贝构造函数
 *
 * @param lo,hi: 拷贝区间[lo,hi)
 * @return
 * @retval None
 */
template <typename T>
Vector<T>::Vector(const Vector<T>& V, int lo, int hi )
{
    this->copy_from(V.m_array, lo, hi);
}

/*!
 * @brief 重写operator=
 *
 * 使用operator=赋值，说明左值已实例化，故需要先释放原的m_array。
 *
 * @param V: 目标Vector
 * @return 返回当前Vector的引用
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
 * @brief 复制数组数据到Vector
 *
 * 直接申请数组资源，若原先已申请数组资源，需要在调用copy_from前释放。
 *
 * @param A: 目标数组
 * @param lo,hi: 下标范围[lo,hi)
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
 * @brief 插入元素到最前面
 *
 * @param ele: 待插入的元素
 * @return 返回新插入元素的下标
 * @retval None
 */
template <typename T>
int Vector<T>::push_front(const T& ele)
{
    return this->insert(0, ele);
}

/*!
 * @brief 插入元素到最后面
 *
 * @param ele: 待插入的元素
 * @return 返回新插入元素的下标
 * @retval None
 */
template <typename T>
int Vector<T>::push_back(const T& ele)
{
    if(this->m_size >= this->m_capacity)
        this->expand();
    this->m_array[this->m_size++] = ele;
    return this->m_size-1;
}

/*!
 * @brief 插入元素到指定下标位置
 *
 * @param index: 指定的插入下标位置
 * @param ele: 待插入的元素
 * @return 返回新插入元素的拉置
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
 * @brief 删除指定下标的元素
 *
 * @param index: 指定的删除下标位置
 * @return 返回被删除的元素
 * @retval None
 */
template <typename T>
T Vector<T>::remove(int index)
{
    // 删除[r, r+1)即可删除单个元素
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
 * @brief 删除下标在范围[lo,hi)的所有元素
 *
 * @param lo,hi: 下标范围[lo,hi)
 * @return 返回删除的元素总数量
 * @retval None
 */
template <typename T>
int Vector<T>::remove(int lo, int hi)
{
    if(lo == hi) return 0;
    while(hi < this->m_size)
        this->m_array[lo++] = this->m_array[hi++];
    this->m_size = lo;
    return hi-lo;
}

/*!
 * @brief 扩展Vector容量
 *
 * @param None
 * @return
 * @retval None
 */
template <typename T>
void Vector<T>::expand()
{
    T* old_ar = this->m_array;
    this->m_capacity *= 2;
    this->m_array = new T[this->m_capacity];
    for(int k = 0; k < m_size; k++)
    {
        this->m_array[k] = old_ar[k];
    }
    delete[] old_ar;
}

/*!
 * @brief 在[lo, hi)查找特定元素
 *
 * 因为是遍历[lo,hi)查找，故时间复杂度为O(n)。
 * 若找到ele，则返回下标，否则返回-1。
 *
 * @param ele: 待查找元素
 * @param lo,hi: 下标范围[lo, hi)
 * @return
 * @retval None
 */
template <typename T>
int Vector<T>::find(const T& ele, int lo, int hi) const
{
    while((lo < hi--) && (ele != this->m_array[hi]));  // compare ele and m_array[hi] after hi--
    return hi;
}

/*!
 * @brief 二分查找(binary search)
 *
 * 查找范围为[lo, hi)，时间复杂度为O(logn)
 * 因为最后需要返回不大于ele的最大元素的下标，故查找区间[lo,hi)需要是有序的。
 *
 * @param ele: 待查找元素
 * @param lo,hi: 下标范围[lo, hi)
 * @return 返回不大于ele的元素的下标
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
        // 没法返回不大于ele的最大元素的下标
        int mi = (lo + hi)/2;
        if (ele < this->m_array[mi]) hi = mi;
        else if (this->m_array[mi] < ele) lo = mi + 1;
        else return mi;
    }
    return -1;
#elif(0)
    while(1 < hi - lo)
    {
        // 2个分支判断，[lo, mi) or [mi, hi)
        // 没法返回不大于ele的最大元素的下标
        int mi = (lo +hi)/2;
        ele < this->m_array[mi] ? hi = mi : lo = mi;
    }
    return (ele == this->m_array[lo] ? lo : -1);
#elif(1)
    while(lo < hi)
    {
        // 2个分支判断，[lo, mi] or (mi, hi)
        // ele < m_array[mi]  : [lo, mi)    : hi = mi   : 有m_array[lo-1] <= ele
        // ele >= m_array[mi] : [mi+1, hi） : lo = mi+1 : 有m_array[mi-1+1] <= ele
        // 所以最后返回的是 "--lo"，即返回不大于ele的最大元素的下标，
        // -1表示Vector所有元素不大于ele。
        int mi = (lo + hi)/2;
        ele < this->m_array[mi] ? hi = mi : lo = mi + 1;
    }
    return --lo;
#endif
}

/*!
 * @brief fibonacci查找
 *
 * 查找范围为[lo, hi)
 *
 * @param ele: 待查找元素
 * @param lo,hi: 下标范围[lo, hi)
 * @return 返回不大于ele的元素的下标
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
 * @brief 对[lo,hi)打乱顺序
 *
 * @param lo,hi: 下标范围[lo, hi)
 * @return
 * @retval None
 */
template <typename T>
void Vector<T>::unsort(int lo, int hi)
{
    T* v = this->m_array + lo;      // v的下标范围为[0, hi-lo)
    for (int k = hi - lo; k > 0; k--)
        dsa::swap(v[k-1], v[dsa::rand_n(k)]);
}


/*!
 * @brief 冒泡排序改进版
 *
 * 排序范围为[lo, hi)
 *
 * @param lo,hi: 下标范围[lo, hi)
 * @return
 * @retval None
 */
template <typename T>
void Vector<T>::bubble_sort(int lo, int hi)
{
#if(0)
    while(!this->bubble(lo, hi--));
#else
    while(lo < hi) hi = this->bubble(lo, hi);

    // 改进版二的直接实现
#if(0)
    while(lo < hi)
    {
        int last = lo;
        int first = lo;
        while (++first < hi)
        {
            if (this->m_array[first-1] > this->m_array[first])
            {
                last = first;
                dsa::swap(this->m_array[first-1], this->m_array[first]);
            }
        }
        hi = last;
    }
#endif
#endif
}

/*!
 * @brief 冒泡排序实现
 *
 * <pre>
 *
 * (1)改进版一
 *  lo            hi
 * [            ][          ]
 *  ------------  ---------
 *  待排序区间W   已排序区间S
 * bubble_sort(lo,hi) : 不断的对[lo,hi)排序，扩大S区间
 * bubble(lo,hi)      : 将W中最大元素交换至S中，同时判判W是否为一个有序序列；
 *                      若W已经为一个有序序列，则排序完成。
 *
 * (2)改进版二
 *  lo            hi
 * [     k      ][          ]
 *  ------------  ---------
 *  待排序区间W   已排序区间S
 * bubble_sort(lo,hi) : 不断的对[lo,hi)排序，扩大S区间
 * bubble(lo,hi)      : 将W中最大元素交换至S中，同时判断W的尾部是否有序；
 *                      若W的[k,hi)已经有序，则下一次对[lo, hi=k)进行排序；
 *                      若k与lo相同，则与改进版一的情况相同。
 * </pre>
 *
 * @param lo,hi: 下标范围[lo, hi)
 * @return
 * @retval None
 */
template <typename T>
int Vector<T>::bubble(int lo, int hi)
{
/* 改进版一 */
#if(0)
    int sorted = 1;
    while(++lo < hi)
    {
        if(this->m_array[lo] < this->m_array[lo-1])
        {
            sorted = 0;
            dsa::swap(this->m_array[lo-1], this->m_array[lo]);
        }
    }
    return sorted;

/* 改进版二 */
#else
    int last = lo;
    while(++lo < hi)
    {
        if(this->m_array[lo] < this->m_array[lo-1])
        {
            // last是右侧已排好序区间的左侧下标
            last = lo;
            dsa::swap(this->m_array[lo-1], this->m_array[lo]);
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
 * @param lo,hi: 下标范围[lo, hi)
 * @return
 * @retval None
 */
template <typename T>
void Vector<T>::merge_sort(int lo, int hi)
{
    if(hi - lo < 2)
        return;     // 只有一个元素
    int mi = (lo + hi) / 2;
    merge_sort(lo, mi);
    merge_sort(mi, hi);
    merge(lo, mi, hi);
}

/*!
 * @brief 归并排序的归并操作
 *
 * @param lo,mi,hi: 将[lo,mi)和[mi, hi)进行合并
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
 * @brief 选择排序
 *
 * <pre>
 * 排序范围为[lo, hi)
 *
 * [    m       ][i          ]
 *  ------------  -----------
 *  待排序区间W   已排序区间S
 *  不断的从W中选出最大者m，放入S的第一个位置i处
 * </pre>
 *
 * @param lo,hi: 下标范围[lo, hi)
 * @return
 * @retval None
 */
template <typename T>
void Vector<T>::selection_sort(int lo, int hi)
{
    while(lo < hi--)
        swap(this->m_array[select_max(lo, hi)], this->m_array[hi]);
}

/*!
 * @brief 在[lo, hi)取出最大者
 *
 * 为保证排序稳定性，若最大值有多个时，返回的一定是最后一个；
 *
 * @param lo,hi: 下标范围[lo, hi)
 * @return
 * @retval None
 */
template <typename T>
int Vector<T>::select_max(int lo, int hi)
{
    int max = hi;
    while(lo < hi--)
    {
        if (this->m_array[hi] > this->m_array[max])
            max = hi;
    }
    return max;
}


/*!
 * @brief 插入排序
 *
 * <pre>
 *
 * 排序范围为[lo, hi)
 *
 * [       i    ][e          ]
 *  ------------  -----------
 *  已排序区间S   待排序区间W
 *
 * 不断将W中第一个元素e，插入到S中位置i处；
 * i为S中元素不大于e的最大元素的位置
 *
 * (1) 基本形式：先search再insert。
 * (2) 改进版：因为S是有序的，故从右向左遍因S，比较与e的大小关系，并进行交换。
 *
 * </pre>
 *
 * @param lo,hi: 下标范围[lo, hi)
 * @return
 * @retval None
 */
template <typename T>
void Vector<T>::insertion_sort(int lo, int hi)
{
#if(0)
    // 基本形式：按基本原理实现的算法，最易理解
    for (int k = lo + 1; k < hi; k ++)
    {
        int index = this->search(this->m_array[k], lo, k) + 1;
        if (index < k)
            this->insert(index, this->remove(k));
    }
#else
    // 改进版
    for (int k = lo + 1; k < hi; k ++)
    {
        // n 即为W的第一个元素
        int n = k;
        T   tmp = this->m_array[n];
        while (n > lo && tmp < this->m_array[n-1])
        {
            this->m_array[n] = this->m_array[n-1];
            n--;
        }
        // 出while循环后，n == lo 或 tmp >= this->m_array[n-1]
        // 故tmp必定是插入到n的位置
        this->m_array[n] = tmp;
    }
#endif
}

/*!
 * @brief 快速排序
 *
 * 排序范围为[lo, hi)
 *
 * @param lo,hi: 下标范围[lo, hi)
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
 * 根据轴点的确定过程，可知快速排序前后，可能打乱相同元素间的相对顺序；
 * 即快速排序是不稳定的。
 *
 * (1)基本形式
 * [p][    ][i     j][    ]
 *     ----           ----
 *      L              R
 * 比较候选轴点p和i和j，将i和j不断的归入到L或R中；
 *
 * (2)变种形式
 * [p][      q][i       ][k----------]
 *    --------  --------
 *        L        R
 * 不断的比较候选轴点p和k
 * p <= k : k归入R中；
 * p > k : k归入L中，即交换i和k，L的长度+1；
 * 最终交换p和q，q做为最终的轴点。
 *
 * </pre>
 *
 * @param lo,hi: 下标范围[lo, hi]，注意，这里可以取到hi
 * @return
 * @retval None
 */
template <typename T>
int Vector<T>::partition(int lo, int hi)
{
    // 随机交换候选轴点，使轴点的位置均匀分布
    dsa::swap(this->m_array[lo], this->m_array[lo + dsa::rand_n(hi-lo+1)]);
    // 候选轴点
    T pivot = this->m_array[lo];
#if(1)
    // 基本形式
    while(lo < hi)
    {
        while(lo < hi && this->m_array[hi] >= pivot) hi--;
        this->m_array[lo] = this->m_array[hi];
        while(lo < hi && this->m_array[lo] <= pivot) lo++;
        this->m_array[hi] = this->m_array[lo];
    }
    this->m_array[lo] = pivot;        // 最终轴点
    return lo;
#else
    // 变种形式
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
 * @brief 希尔排序
 *
 * 排序范围为[lo, hi)
 *
 * <pre>
 *
 * (1) 希尔排序过程
 * 将整个序列视作一个矩阵，逐列各自排序w-sorting (w为矩阵列数)
 *
 * 排序序列:  8 1 5 6 9 4 3 7 2
 * 步长序列: [1, 2, 3, 5]
 * 5-sorting : 8 1 5 6 9  =>  4 1 5 2 9  =>  4 1 5 2 9 8 3 7 6
 *             4 3 7 2        8 3 7 6
 *
 * 3-sorting : 4 1 5  =>  2 1 5  =>  2 1 5 3 7 6 4 9 8
 *             2 9 8      3 7 6
 *             3 7 6      4 9 8
 *
 * 2-sorting : 2 1  =>  2 1 => 2 1 4 3 5 6 7 9 8
 *             5 3      4 3
 *             7 6      5 6
 *             4 9      7 9
 *             8        8
 *
 * 1-sorting : 1 2 3 4 5 6 7 8 9
 *
 * 进行w-sort时，使用选择排序；
 * 因为开始的时候，w更大，列元素个数少，逆序对少，选择排序消耗少；
 * 等到后面的时候，w更小，列元素个数多，但逆序对少，选择排序消耗少；
 *
 * (2) 线性组合
 * f=ma+nb : a,b的线性组合（m和n为自然数）
 * N(a,b) : 对任意整数 m,n，所有满足 f!= ma + nb 的f的集合
 * max(N(a,b)) = (a-1)(b-a)-1 = ab-a-b
 *
 * (3) 间隔有序
 * h-ordered : 序列s[0,n)对于任何 0<= i < n-h，都有s[i] <= s[i+h]；
 *
 * 任一个序列进行h-sorting后，必定是h-ordered；
 * 若一个序列同时为g-ordered和g-ordered，则序列也为(mg+nh)-ordered，m和n为自然数；
 *
 * </pre>
 *
 * @param lo,hi: 下标范围[lo, hi)
 * @return
 * @retval None
 */
template <typename T>
void Vector<T>::shell_sort(int lo, int hi)
{
    // 步长序列(step sequence)，也即矩阵的列数: min = 1, max < m_size
#if(0)
    // 希尔步长序列：2^k
    // 递推公式：w[0] = 1, w[i] = w[i-1] * 2
    for (int k = (hi - lo)/2; k > 0; k /= 2)
        this->shell_insertion(k, lo, hi);
#elif(1)
    // Hibbard步长序列(相邻步长互素)：2^k-1
    // 递推公式：w[0] = 1, w[i] = 2 * w[i-1] + 1
    Vector<int> ss;
    int k = 1;
    while (k < this->m_size)
    {
        ss.push_back(k);
        k = 2 * k + 1;
    }
    for (k = ss.size()-1; k >= 0; k --)
        this->shell_insertion(ss[k], lo, hi);
#elif(0)
    // Knuth步长序列：(3^k-1)/2
    // 递推公式：w[0] = 1, w[i] = 3 * w[i-1] + 1
    Vector<int> ss;
    int k = 1;
    while (k < this->m_size)
    {
        ss.push_back(k);
        k = 3 * k + 1;
    }
    for (k = ss.size()-1; k >= 0; k --)
        this->shell_insertion(ss[k], lo, hi);
#endif
}

/*!
 * @brief shell排序中的插入排序算法
 *
 * @param lo,hi: 下标范围[lo, hi)
 * @param w: 步长值，也即矩阵列宽
 * @return
 * @retval None
 */
template <typename T>
void Vector<T>::shell_insertion(int w, int lo, int hi)
{
#if(1)
    // 每w次循环，完成对所有列的同一行的插入排序
    // 第一行元素： lo   , lo+1   , ... lo+w-1
    // 第二行元素： lo+w , lo+w+1 , ...
    for (int k = lo + w; k < hi; k ++)
    {
        // 此部分程序参照insertion_sort
        int n = k;
        T   tmp = this->m_array[n];
        while (n >= lo+w && tmp < this->m_array[n-w])
        {
            this->m_array[n] = this->m_array[n-w];
            n -= w;
        }
        this->m_array[n] = tmp;
    }

#else
    // 依次对第 0,1,2...w 列进行排序(排完第0列，才能排第1列······)
    int cow = ((hi-lo) + w - 1) / w;        // 向上取整，即为矩阵的行数
    for (int k = 0; k < w; k ++)            // 对所有列进行插入排序
    {
        int sl = lo + k, sh = lo + k+cow*w; // (插入排序)列下标范围[sl,sh)
        if (sh > hi) sh -= w;               // 防止列下标超范围
        for (int s = sl + w; s < sh; s += w)// 对列元素进行插入排序
        {
            // 此部分程序参照insertion_sort
            int n = s;
            T   tmp = this->m_array[n];
            while (n > sl && tmp < this->m_array[n-w])
            {
                this->m_array[n] = this->m_array[n-w];
                n -= w;
            }
            this->m_array[n] = tmp;
        }
    }
#endif
}


/*!
 * @brief 遍历数组
 *
 * @param visit: 访问函数
 * @return
 * @retval None
 */
template <typename T>
template <typename VST>
void Vector<T>::traverse(VST& visit)
{
    for (int k = 0; k < this->m_size; k ++)
        visit(this->m_array[k]);
}

} /* dsa */

#endif /* ifndef _VECTOR_H */
