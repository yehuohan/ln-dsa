
//==============================================================================
/*!
 * @file majority.h
 * @brief 众数算法
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================


#ifndef DSAS_MAJORITY_H
#define DSAS_MAJORITY_H

#include "../vector.h"

namespace dsa
{

/*!
 * @addtogroup Example
 *
 * @{
 */

template <typename T> bool majority(const dsa::Vector<T>& vec, T& maj);
template <typename T> static bool is_majority(const dsa::Vector<T>& vec, const T& maj);
template <typename T> static T maj_candidate(const dsa::Vector<T>& vec);

/*!
 * @brief
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
 * @brief
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

#endif /* ifndef DSAS_MAJORITY_H */
