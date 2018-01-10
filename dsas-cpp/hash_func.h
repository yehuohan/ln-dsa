//==============================================================================
/*!
 * @file hash_func.h
 * @brief 计算Hash的函数
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef _HASH_FUNC_H
#define _HASH_FUNC_H

#include "string.h"

namespace dsa
{

/*!
 * @addtogroup LHash
 *
 * @{
 */

/** 计算出的Hash值均为uint类型 */
typedef unsigned int uint;

/** Hash仿函数模板 */
template <typename T> struct Hash;

/*!
 * @name Hash函数实例化
 * @{
 */

/** 计算Hash<bool> */
template <> struct Hash<bool>
{ uint operator() (bool h) const {return static_cast<uint>(h);} };

/** 计算Hash<char> */
template <> struct Hash<char>
{ uint operator() (char h) const {return static_cast<uint>(h);} };

/** 计算Hash<unsigned char> */
template <> struct Hash<unsigned char>
{ uint operator() (unsigned char h) const {return static_cast<uint>(h);} };

/** 计算Hash<char*> */
template <> struct Hash<char*>
{
    uint operator() (char h[]) const
    {
        int hc = 0;
        const char* p = h;
        while (*p != '\0')
        {
            hc = (hc << 5) | (hc >> 27);
            hc += static_cast<int>(*p);         // 近似“多项式散列码”，参考秦九韶算法
            p++;
        }
        return static_cast<uint>(hc);
    }
};

/** 计算Hash<String> */
template <> struct Hash<dsa::String>
{
    uint operator() (const dsa::String& h) const
    {
        int hc = 0;
        for (int k = 0; k < h.size(); k ++)
        {
            hc = (hc << 5) | (hc >> 27);
            hc += static_cast<int>(h[k]);       // 近似“多项式散列码”，参考秦九韶算法
        }
        return static_cast<uint>(hc);
    }
};

/** 计算Hash<int> */
template <> struct Hash<int>
{ uint operator() (int h) const {return static_cast<uint>(h);} };

/** 计算Hash<unsigned int> */
template <> struct Hash<unsigned int>
{ uint operator() (unsigned int h) const {return static_cast<uint>(h);} };

/** 计算Hash<float> */
template <> struct Hash<float>
{ uint operator() (float h) const {return h != 0.0 ? (*(uint*)&h) : 0;} };

/** 计算Hash<double> */
template <> struct Hash<double>
{ uint operator() (double h) const {return h != 0.0 ? (*(uint*)&h) : 0;} };

/*! @} */

/*! @} */

} /* dsa */

#endif /* ifndef _HASH_FUNC_H */

