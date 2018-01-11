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
    bool operator() (const T& lhs, const T& rhs) const {return lhs < rhs;}
};

/*!
 * @name 比较函数模板
 *
 * <pre>
 * 被比较的对象，必须重写 operator<。
 *
 * 理想情况是，自己实现类的所有比较操作符。
 * 使用比较函数模板则只有实现 operator< 即可。
 *
 * </pre>
 *
 * @{
 */

/** 用 < 实现 < */
template <typename T> bool less_than    (const T& a, const T& b) {return a < b;}
/** 用 < 实现 > */
template <typename T> bool greater_than (const T& a, const T& b) {return b < a;}
/** 用 < 实现 == */
template <typename T> bool is_equal     (const T& a, const T& b) {return !(a < b || b < a);}
/** 用 < 实现 != */
template <typename T> bool not_equal    (const T& a, const T& b) {return  (a < b || b < a);}
/** 用 < 实现 <= */
template <typename T> bool less_equal   (const T& a, const T& b) {return (less_than(a,b) || is_equal(a,b));}
/** 用 < 实现 >= */
template <typename T> bool greater_equal(const T& a, const T& b) {return (greater_than(a,b) || is_equal(a,b));}

/*! @} */


/*!
 * @brief 比较类模板
 *
 * 将数据封装到一个类中，实现比较操作符、赋值操作符、拷贝构造函数等。
 *
 */
template <typename T, typename L=dsa::Less<T> >
struct CmpOperator
{
    T   val;
    L   lt;

    CmpOperator(T _val = T()) : val(_val) {}
    CmpOperator(const CmpOperator<T,L>& rhs) : val(rhs.val) {}

    /** 重载= */
    CmpOperator& operator= (const CmpOperator<T,L>& rhs) {val = rhs.val; return *this;}
    /** 重载= */
    CmpOperator& operator= (const T& rhs) {val = rhs; return *this;}

    /*!
     * @name 实现CmpOperator之间的比较
     * @{
     */ 
    bool operator<  (const CmpOperator<T,L>& c) const {return lt(val, c.val);}
    bool operator>  (const CmpOperator<T,L>& c) const {return lt(c.val, val);}
    bool operator== (const CmpOperator<T,L>& c) const {return !(lt(val, c.val) || (c.val, val));}
    bool operator!= (const CmpOperator<T,L>& c) const {return  (lt(val, c.val) || (c.val, val));}
    bool operator<= (const CmpOperator<T,L>& c) const {return (*this > c || *this == c);}
    bool operator>= (const CmpOperator<T,L>& c) const {return (*this < c || *this == c);}
    /*! @} */

    /*!
     * @name 实现CmpOperator与T之间的比较
     * @{
     */
    bool operator<  (const T& v) const {return lt(val, v);}
    bool operator>  (const T& v) const {return lt(v, val);}
    bool operator== (const T& v) const {return !(lt(val, v) || lt(v, val));}
    bool operator!= (const T& v) const {return  (lt(val, v) || lt(v, val));}
    bool operator<= (const T& v) const {return (*this < v || *this == v);}
    bool operator>= (const T& v) const {return (*this > v || *this == v);}
    /*! @} */
};

/*! @} */

} /* dsa */

#endif /* ifndef DSAS_COMPARE_H */
