
//==============================================================================
/*!
 * @file algorithm.h
 * @brief 一些相关算法
 *
 * @date 2018-10-01
 * @version
 * @author
 * @copyright
 */
//==============================================================================


#ifndef DSA_ALGORITHM_H
#define DSA_ALGORITHM_H

#include "../vector.h"

namespace dsa
{

/*!
 * @addtogroup Share
 *
 * @{
 */


/*!
 * @brief 选取第k大小的元素
 *
 * 第k大小的元素，即为有序向量下标为k的元素。
 * 根据快速排序的算法进行构造，迭代的查找轴点，直至轴点下标为k。
 *
 * @param vec: 在向量vec中查找第k大小的元素
 * @param k: 指第k大小的元素，0 <= k < vec.size()
 * @return
 * @retval None
 */
template <typename T>
T quick_select(dsa::Vector<T> vec, int k)
{
    int lo, hi;
    for (lo = 0, hi = vec.size()-1; lo < hi;)
    {
        int i = lo, j = hi;
        T pivot = vec[lo];
        while(i < j)
        {
            while(i < j && vec[j] >= pivot) j--;
            vec[i] = vec[j];
            while(i < j && vec[i] <= pivot) i++;
            vec[j] = vec[i];
        }
        vec[i] = pivot;
        if (k < i) hi = i - 1;
        else if(k > i) lo = i + 1;
        else return vec[i];
    }
    return vec[lo];
}


template <typename T> bool majority(const dsa::Vector<T>& vec, T& maj);
template <typename T> static bool is_majority(const dsa::Vector<T>& vec, const T& maj);
template <typename T> static T maj_candidate(const dsa::Vector<T>& vec);

/*!
 * @brief 求取众数
 *
 * <pre>
 * 众数：无序向量中，若有一半以上的元素相同，则称之为众数。
 * 频繁数：无序向量中，出现次数最多的元素
 *
 * 算法时间复杂度：
 * maj_candidate = O(n)
 * is_majority   = O(n)
 *
 * </pre>
 *
 * @param vec: 无序向量序列
 * @param maj: 若有众数，则被赋值为众数
 * @return
 * @retval None
 */
template <typename T>
bool majority(const dsa::Vector<T>& vec, T& maj)
{
    maj = maj_candidate(vec);
    return is_majority(vec, maj);
}

/*!
 * @brief 判断是否为众数
 *
 * 只需要判断一个元素的出现次数的2倍，是否大于了总元素数
 *
 * @param vec: 无序向量序列
 * @param maj: 待判断的元素
 * @return
 * @retval None
 */
template <typename T>
static bool is_majority(const dsa::Vector<T>& vec, const T& maj)
{
    int num = 0;
    for (int k = 0; k < vec.size(); k ++)
        if (maj == vec[k]) num ++;
    return 2*num > vec.size();
}

/*!
 * @brief 求取可能的众数
 *
 * <pre>
 *
 * O(n)的时间复杂度。
 *
 * 若在向量A中，元素m出现的次数大于一半，即众数为元素m：
 * [mmmmmmmm][*****]
 *
 * (1)无论m和*顺序如何，对任意一个前缀P，取任一个元素进行比较操作，当某个元素x正好占一半时，
 * 若x==m: 则A-P中，m必定仍仍然大于一半。
 * 若x!=m: 则A-P中，m必定更加的大于一半。
 * [ P  ][   A-P   ]
 * 剪除P后，对A-P继续进行比较操作，当遍历所元素后，
 * 最终会得到一个出现次数大于一半的元素x，且必定是众数m。
 *
 * (2)若在向量A中，没有众数，相同的操作也会得出一个元素x。
 *
 * 所以，对于最后得到的元素x，还需要验证是否为众数。
 *
 * </pre>
 *
 * @param vec: 无序向量序列
 * @return
 * @retval None
 */
template <typename T>
static T maj_candidate(const dsa::Vector<T>& vec)
{
    T maj;
    int cnt = 0;
    for (int k = 0; k < vec.size(); k ++)
    {
        if (cnt == 0)
        {
            maj = vec[k];
            cnt++;
        }
        else
            (maj == vec[k]) ? cnt++ : cnt--;
    }
    return maj;
}


/*! @} */

} /* dsa */

#endif /* ifndef DSA_ALGORITHM_H */
