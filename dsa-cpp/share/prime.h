//==============================================================================
/*!
 * @file prime.h
 * @brief 获取素数
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef DSAS_PRIME_H
#define DSAS_PRIME_H

#include "../bitmap.h"
#include "../input-data/prime-1048576-bitmap.h"
#include "../input-data/prime-1048576-4k3-bitmap.h"

namespace dsa
{
    
/*!
 * @addtogroup Share
 *
 * @{
 */

#define PRIME_MAX_1048576       1048576

/*!
 * @brief 查表法获取[low, n)内最最小素数
 *
 * @param low,n: 素数范围
 * @param file: 保存素数的Bitmap文件 
 * @return
 * @retval None
 */
inline int prime_file(int low, int n, const char* file)
{
    dsa::Bitmap bm(file, n);
    while (low < n)
    {
        if (bm.test(low))
            return low;
        low ++;
    }
    return low;
}

/*!
 * @brief 查表法获取[low, n)内最最小素数
 *
 * @param low,n: 素数范围
 * @param ch: 保存素数的Bitmap数组
 * @param size: 保存素数的Bitmap数组长度
 * @return
 * @retval None
 */
inline int prime_array(int low, int n, const char ch[], int size)
{
    dsa::Bitmap bm(size, ch);
    while (low < n)
    {
        if (bm.test(low))
            return low;
        low ++;
    }
    return low;
}

/*!
 * @brief 获取[low, 1048576)内最最小素数
 *
 * @param low: 素数范围下界
 * @return
 * @retval None
 */
inline int prime_1048576(int low)
{
    return prime_array(low, PRIME_MAX_1048576, prime_1048576_bitmap, sizeof(prime_1048576_bitmap)/sizeof(char));
}

/*!
 * @brief 获取[low, 1048576)内最最小的 4k+3 形式素数（模4余3的素数）
 *
 * @param low: 素数范围下界
 * @return
 * @retval None
 */
inline int prime_1048576_4k3(int low)
{
    return prime_array(low, PRIME_MAX_1048576, prime_1048576_4k3_bitmap, sizeof(prime_1048576_bitmap)/sizeof(char));
}

/*! @} */

} /* dsa */

#endif /* ifndef DSAS_PRIME_H */
