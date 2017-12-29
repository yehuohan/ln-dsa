//==============================================================================
/*!
 * @file time.h
 * @brief 用于计算时间消耗
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef DSAS_TIME_H
#define DSAS_TIME_H

#include "macro.h"
#if defined DSAS_WIN

#elif defined DSAS_LINUX

#endif

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
 * @brief clock_t的封装
 *
 */
typedef clock_t ClockTime;

/*!
 * @brief 获取时间点
 *
 * @param None
 * @return
 * @retval None
 */
inline ClockTime get_clock()
{
    return std::clock();
}

/*!
 * @brief 计算时间差(ms)
 *
 * @param s,e: 开始与结束的时间(ClockTime)
 * @return
 * @retval None
 */
inline double get_time(const ClockTime& s, const ClockTime& e)
{
    return (double)(e-s) / CLOCKS_PER_SEC*1000;
}

/*! @} */
    
} /* dsa */
#endif /* ifndef DSAS_TIME_H */
