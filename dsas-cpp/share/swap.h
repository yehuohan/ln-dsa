
//==============================================================================
/*!
 * @file swap.h
 * @brief 对调函数
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef DSAS_SWAP_H
#define DSAS_SWAP_H

namespace dsa
{

/*!
 * @addtogroup Share
 *
 * @{
 */


/*!
 * @brief 交换函数
 *
 * 交换对像必须有正确的拷贝构造函数
 *
 * @param a,b 交换对象
 * @return
 * @retval None
 */
template <typename T>
void swap(T& a, T& b)
{
    T t = a;
    a = b;
    b = t;
}

/*! @} */
    
} /* dsa */ 

#endif /* ifndef DSAS_SWAP_H */

