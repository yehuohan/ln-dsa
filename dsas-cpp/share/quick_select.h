
//==============================================================================
/*!
 * @file quick_select.h
 * @brief 选出第k大小的元素
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _QUICK_SELECT_H
#define _QUICK_SELECT_H

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


/*! @} */

} /* dsa */

#endif /* ifndef _QUICK_SELECT_H */
