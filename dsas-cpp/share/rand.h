
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

#ifndef DSAS_RAND_H
#define DSAS_RAND_H

#include <ctime>
#include <cstdlib>

namespace dsa
{

/*!
 * @addtogroup Share
 *
 * @{
 */

/*!
 * @brief 设置随机种子
 *
 * 使用rand_n前，调用一次
 *
 * @param None
 * @return
 * @retval None
 */
inline void rand_init()
{
    std::srand((unsigned)std::time(nullptr));
}

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
inline int rand_n(int N)
{
    return std::rand() % N;
}

/*! @} */

} /* dsa */

#endif /* ifndef DSAS_RAND_H */

