//==============================================================================
/*!
 * @file compare.h
 * @brief 用 < 实现所有比较函数
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef DSAS_COMPARE_H
#define DSAS_COMPARE_H

namespace dsa
{

/*!
 * @addtogroup Share
 *
 * @{
 */

/*!
 * @brief Less仿函数
 *
 */
template <typename T> struct Less
{
    bool operator()(const T& lhs, const T& rhs) {return lhs < rhs;};
};

/** 用 < 实现 < */
template <typename T> bool less_than   (const T& a, const T& b) {return a < b;}
/** 用 < 实现 > */
template <typename T> bool greater_than(const T& a, const T& b) {return b < a;}
/** 用 < 实现 == */
template <typename T> bool is_equal    (const T& a, const T& b) {return !(a < b || b < a);}
/** 用 < 实现 != */
template <typename T> bool not_equal   (const T& a, const T& b) {return  (a < b || b < a);}

/*! @} */

} /* dsa */

#endif /* ifndef DSAS_COMPARE_H */
