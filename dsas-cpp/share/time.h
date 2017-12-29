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
#if defined DSAS_LINUX
    #include <sys/time.h>
    #include <unistd.h>
#elif defined DSAS_WIN
    #include <windows.h>
#else
    #include <ctime>
    #include <cstdlib>
#endif

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
#if defined DSAS_LINUX
typedef long double ClockTime;
#elif defined DSAS_WIN
typedef LONGLONG    ClockTime;
#else
typedef clock_t     ClockTime;
#endif

/*!
 * @brief 获取时间点
 *
 * @param None
 * @return
 * @retval None
 */
inline ClockTime get_clock()
{
#if defined DSAS_LINUX
    struct timeval time;
    gettimeofday(&time, nullptr);
    return 100000.0f * (long double)time.tv_sec + (long double)time.tv_usec;
#elif defined DSAS_WIN
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    return time.QuadPart;
#else
    return std::clock();
#endif
}

/*!
 * @brief 计算时间差(ms)
 *
 * @param s,e: 开始与结束的时间(ClockTime)
 * @return
 * @retval None
 */
inline double get_time_ms(const ClockTime& s, const ClockTime& e)
{
#if defined DSAS_LINUX
    return (double)(e-s) / 1000.0f;
#elif defined DSAS_WIN
    LARGE_INTEGER cpu_freq;
    QueryPerformanceFrequency(&cpu_freq);
    return (double)(e-s) * 1000.0f / (double)cpu_freq.QuadPart;
#else
    return (double)(e-s) / CLOCKS_PER_SEC*1000.0f;
#endif
}

/*! @} */
    
} /* dsa */
#endif /* ifndef DSAS_TIME_H */
