//==============================================================================
/*!
 * @file string.h
 * @brief 字符串相关算法
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================

#ifndef DSAS_STRING_H
#define DSAS_STRING_H

#include <iostream>
#include "vector.h"
#include "share/swap.h"

namespace dsa
{

/*!
 * @addtogroup LString
 *
 * @{
 */

int     str_cpy(char*, const char*, int);
int     str_len(const char*);
int     str_cmp(const char*, const char*);
void    str_set(const char*, char, int);

/*!
 * @brief 字符串类
 *
 * <pre>
 * 串
 *
 * 相等：
 *      S[0,n) = T[0,m)
 *      长度相等，且对应的字符相同
 * 子串：
 *      substr(i,k) = S[i, i+k), 0<= i < n, 0 <= k
 *      从S[i]起的连续k个字符
 * 前缀：
 *      prefix(k) = substr(0,k) = S[0,k), 0 <= k <= n
 *      最靠前k个字符
 * 后缀：
 *      suffix(k) = substr(n-k, k) = S[n-k, n), 0 <= k <= n
 *      最靠后的k个字符
 * 空串：
 *      S[0, n=0)
 * </pre>
 *
 */
class String : protected dsa::Vector<char>
{
protected:
    /** 添加字符串结尾标记'\0' */
    void    addZero()
    {
        if(this->m_size >= this->m_cap)
            this->expand();
        this->m_array[this->m_size] = '\0';
    };

public:
    String() : dsa::Vector<char>() {}
    String(const char* str) : dsa::Vector<char>(str, str_len(str)) {this->addZero();}
    String(const char* str, int n) : dsa::Vector<char>(str, n) {this->addZero();}
    String(const char* str, int lo, int hi) : dsa::Vector<char>(str, lo, hi) {this->addZero();}
    String(const String& str) : dsa::Vector<char>(str.m_array, str.m_size) {this->addZero();}
    String(const String& str, int lo, int hi) : dsa::Vector<char>(str.m_array, lo, hi) {this->addZero();}

    /** 重写赋值(=)运算符 */
    String& operator=(const char* str)
    {
        if(this->m_array) delete[] this->m_array;
        this->copy_from(str, 0, str_len(str));
        this->addZero();
        return *this;
    }
    /** 重写赋值(+=)运算符 */
    String& operator+=(const char c)
    {
        this->push_back(c);
        this->addZero();
        return *this;
    }
    /** 重写赋值(+=)运算符 */
    String& operator+=(const char* str)
    {
        for (int k = 0; k < str_len(str); k ++)
            this->push_back(str[k]);
        this->addZero();
        return *this;
    }
    /** 重写输出(<<)运算符 */
    friend std::ostream& operator<< (std::ostream& out, dsa::String& str) {str.addZero(); out << str.m_array; return out;}
    /** 重写输出(<<)运算符 */
    friend std::ostream& operator<< (std::ostream& out, const dsa::String& str) {out << str.m_array; return out;}
    /** 重写[]，没有边界检测，可以修改m_array */
    char& operator[] (int k) {return this->m_array[k];}
    /** 重写[]，没有边界检测，不能修改m_array */
    const char& operator[] (int k) const {return this->m_array[k];}
    /** 重写< */
    bool operator< (const String& str) const {return (str_cmp(this->m_array, str.m_array) == -1);}
    /** 重载> */
    bool operator> (const String& str) const {return (str_cmp(this->m_array, str.m_array) == 1);}
    /** 重载== */
    bool operator== (const String& str) const {return (str_cmp(this->m_array, str.m_array) == 0);}
    /** 重载!= */
    bool operator!= (const String& str) const {return (str_cmp(this->m_array, str.m_array) != 0);}
    /** 重载<= */
    bool operator<= (const String& str) const {return (str_cmp(this->m_array, str.m_array) <= 0);}
    /** 重载>= */
    bool operator>= (const String& str) const {return (str_cmp(this->m_array, str.m_array) >= 0);}

    /** 返回char指针，可以修改m_array */
    char*   data() {return this->m_array;}
    /** 返回char常指针，不能修改m_array */
    const char* data() const {return this->m_array;}
    /** 返回字符串长度，不包括'\0' */
    int     size() const {return this->m_size;}
    /** 返回下标为k的char，没有边界检测，可以修改m_array */
    char&   at(int k) {return this->m_array[k];}
    /** 返回下标为k的char，没有边界检测，不能修改m_array */
    const char& at(int k) const {return this->m_array[k];}
    /** 清空字符串 */
    void    clear() {this->m_size = 0;}
    /** 反转字符串 */
    void    reverse()
    {
        for (int i = 0, j = this->m_size - 1; i < j; i ++, j --)
            dsa::swap(this->m_array[i], this->m_array[j]);
    }
    /** 字符栈push */
    void    push(char c) {this->push_back(c); this->addZero();}
    /** 字符栈pop */
    char    pop()
    {
        char c = '\0';
        if (this->m_size > 0)
        {
            c = this->m_array[this->m_size-1];
            this->m_size --;
            this->m_array[this->m_size] = '\0';
        }
        return c;
    }

    /** 子串下标范围[i, k) */
    String  substr(int i, int k) {return String(*this, i, k);}
    /** 前缀下标范围[0, k) */
    String  prefix(int k) {return String(*this, 0, k);}
    /** 后缀下标范围[size-k, size) */
    String  suffix(int k) {return String(*this, this->size() - k, this->size());};
    //String  join();
    //bool    equal();
};

/*! @} */

/*!
 * @brief 复制字符串
 *
 * @param dst: 目标字符串，内存长度为size+1，以'\0'结尾
 * @param src: 源字符串，以'\0'结尾
 * @param size: 复制的字符串个数，不包括'\0'
 * @return 返回复制的字符串个数
 * @retval None
 */
int str_cpy(char* dst, const char* src, int size)
{
    int len = 0;
    while (*src != '\0' && len++ < size)
        *dst++ = *src++;
    *dst = '\0';
    return len;
}

/*!
 * @brief 获取字符串长度
 *
 * 长度不包括'\0'
 *
 * @param str: 字符串，以'\0'结尾
 * @return
 * @retval None
 */
int str_len(const char* str)
{
    int len = 0;
    while(*str++ != '\0')
        len ++;
    return len;
}

/*!
 * @brief 字串符比较
 *
 * @param a,b: 待比较的字符串
 * @return
 * @retval 1: a > b
 * @retval 0: a == b
 * @retval -1: a < b
 */
int str_cmp(const char* a, const char* b)
{
    // 无论哪个先到达'\0'，均会因 *a != *b 退出循环
    while(*a && *a == *b)
    {
        a++;
        b++;
    }

    if (*(unsigned char*)a > *(unsigned char*)b)
        return 1;
    if (*(unsigned char*)a < *(unsigned char*)b)
        return -1;
    return 0;
}

/*!
 * @brief 填充字符串
 *
 * @param str: 待填充的字符串
 * @param ch: 填充字符
 * @param size: 字符串长度
 * @return
 * @retval None
 */
void str_set(char* str, char ch, int size)
{
    for (int k = 0; k < size; k ++)
        *(str + k) = ch;
}

} /* dsa */

#endif /* ifndef DSAS_STRING_H */
