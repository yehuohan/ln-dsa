
//==============================================================================
/*!
 * @file rand.h
 * @brief 随机数
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _RAND_H
#define _RAND_H

#include <cstdlib>
#include <ctime>

namespace dsa
{

/*!
 * @addtogroup Share
 *
 * @{
 */


/*!
 * @brief 返一个位于[0,n)随机数
 *
 * 随机数范围[0, N)；
 *
 * 这里使用std::rand()来生成随机数，故N的值不能超过std::rand()的范围。
 *
 * @param N: 取模值
 * @return
 * @retval None
 */
int rand_n(int N)
{
    std::srand((unsigned)time(nullptr));
    return std::rand() % N;
}

/*! @} */

} /* dsa */

#endif /* ifndef _RAND_H */

