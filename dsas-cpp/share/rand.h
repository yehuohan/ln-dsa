
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
 * @brief 返一个随机数
 *
 * 随机数范围[0, N)
 *
 * @param N: 取模值
 * @return
 * @retval None
 */
int rand(int N)
{
    std::srand((unsigned)time(nullptr));
    return std::rand() % N;
}

/*! @} */

} /* dsa */

#endif /* ifndef _RAND_H */

