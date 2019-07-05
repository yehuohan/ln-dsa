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

#ifndef _STRING_H
#define _STRING_H

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

int     match_bf1(char* P, char* T);
int     match_bf2(char* P, char* T);

int     match_kmp(char*, char*);
int*    build_next(char*);
int*    build_next_improved(char*);

int     match_bm_bc(char*, char*);
int     match_bm_bcgs(char*, char*);
int*    build_bc(char*);
int*    build_gs(char*);


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
    friend std::ostream& operator<< (std::ostream& out, dsa::String& str) {out << str.m_array; return out;}
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


/*!
 * @brief  蛮力匹配(Brute-force-1)
 *
 * <pre>
 *
 * 时间复杂度：
 * len(P) = m , len(T) = n
 * O(n+m) <= BF <= O(n*m)
 *
 * 示意图：
 *                            i
 * Text: ------ [           ] X -------------
 * Pattern:     [           ] Y [     ]
 *                            j
 * </pre>
 *
 * @param P: Pattern，模式字符，即待匹配的字符
 * @param T: Text，文本字符
 * @return
 * @retval None
 */
int match_bf1(char* P, char* T)
{
    int n = str_len(T), i = 0;
    int m = str_len(P), j = 0;

    while(j < m && i < n)
    {
        if (T[i] == P[j])
        {
            i++;
            j++;
        }
        else
        {
            i -= (j-1);     // T回退，即回退了 j 个字符，再前进 1 个字符
            j = 0;          // P复位，即回退了 j 个字符
        }
    }
    return i-j;             // 若匹配成功，则i-j为P在T首次出现位置（第一个字符）的下标
}

/*!
 * @brief  蛮力匹配(Brute-force-2)
 *
 * <pre>
 *
 * 时间复杂度：
 * len(P) = m , len(T) = n
 * O(n+m) <= BF <= O(n*m)
 *
 * 示意图：
 *               i           i+j
 * Text: ------ [           ] X -------------
 * Pattern:     [           ] Y [     ]
 *                            j
 * </pre>
 *
 * @param P: Pattern，模式字符，即待匹配的字符
 * @param T: Text，文本字符
 * @return
 * @retval None
 */
int match_bf2(char* P, char* T)
{
    int n = str_len(T), i = 0;
    int m = str_len(P), j;

    for (i = 0; i < n-m+1; i++)
    {
        for (j = 0; j < m; j++) // 逐字符对比P中的字符
        {
            if (T[i+j] != P[j])
                break;          // 若失配，i指向下一字符
        }
        if (m <= j)             // j指向了P的最后一个字符
            break;
    }

    return i;
}


/*!
 * @brief KMP匹配算法
 *
 * <pre>
 *
 * KMP算法：匹配概率越高，优势越明显；适合小字符表。
 * 时间复杂度：
 * len(P) = m , len(T) = n
 * KMP = O(n+m)
 *
 * (1)KMP的基本思想如下：
 *                             失配点
 *                           /
 * Text    :  c h i n c h i *
 *            0 1 2 3 4 5 6 7 8 9  -> 字符的下标j
 * Pattern :  c h i n c h i l l a
 *           -1 0 0 0 0 1 2 3 0 0  -> next[j]
 * next[j] :          c h i n c h i l l a

 * 在 P[j=7]=l 匹配失败时，不必从P[j=0]重新开始匹配，而是从 next[j=7]=P[j=3]=n 开始匹配；
 * 因为 P[j=4,5,6]=chi 和 P[j=0,1,2] 相同的，不需要再次匹配（因此KMP算法需要先建立next表）；
 *
 * (2)Next[j]的建立：
 *                                        i -> 失配点下标
 * Text: ---------- [     ][  P[j-t,j)  ] x ----------
 *                  |       ------------|
 *                  |     P[0,j)的真后缀|
 *                  |                   |
 *                  [  P的前缀：P[0,j)  ]
 *                  |                   |
 *                  |                   | j -> 失配点下标
 * Pattern:         [   P[0,t)   ][     ] y -----
 *                  |------------       |
 *                  |P[0,j)的真前缀     |
 *                  |                   |
 *                  |                   | t -> 新的比较点
 *                  |  j-t  [   P[0,t)  ] z -------
 *                           -----------
 *                          P[0,j)的真前缀
 *      当P[j-t,j) 与 P[0,t)相等，则无需要再比较，直接从新的比较点t开始匹配
 *
 * 对任意失配点j，next[j]的值为：
 * next[j] = N(P,j) = { 0 <= t < j | P[0,t) == P[j-t, j) }
 * 即：
 *      在P的前缀P[0,j)中，P[0,j)的真前缀P[0,t)和真后缀P[j-t,j)匹配的长度，就是next[j]；
 *      若有多个匹配的真前缀和真后缀，则取长度最长的（即使得移动距离j-t最小）；
 *      因为“大”长度的，肯定包含了“小”长度真前缀和真后缀。
 *
 * 可推出：
 * next[j+1] <= next[j] + 1
 * 当且仅当 P[j] == P[next[j]] 时取等号
 * 理解如下：
 *              j+1
 * [   P[0,j+1) |   ]
 *             j|
 * [   P[0,j)  ||   ]
 * [    *******#?   ]       => P[j] = #, next[j] = 7, next[j] < j （真后缀的长度比P[0,j)的长度小）
 *     [*******#?       ]   => P[7] = # = P[next[j]]，则有P[j] = P[next[j]]
 *      --------
 *     此段是 P[0,j) 的真前缀和真后缀，其长度，也即 * 的个数，就是next[j] = 7 (注意P[0,j)未包括j)；
 *     而next[j+1]相对于next[j]多了个 #，即P[0,j+1)的真前缀和真后缀匹配的长度加1
 *
 * </pre>
 *
 * @param P: Pattern，模式字符，即待匹配的字符
 * @param T: Text，文本字符
 * @return
 * @retval None
 */
int match_kmp(char* P, char* T)
{
    int* next = build_next_improved(P);
    int n = str_len(T), i = 0;
    int m = str_len(P), j = 0;

    while(j < m && i < n)
    {
        // j = next[j] = -1: 说明在P的首字符发生失配
        // P[-1]为假想的通配符，只要 j=-1<0，则必定匹配
        if (j < 0 || T[i] == P[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];    // 失配时，下一次将T[i]与P[next[j]]进行比对
    }
    delete[] next;
    return i-j;             // 若匹配成功，则i-j为P在T首次出现位置（第一个字符）的下标
}

/*!
 * @brief 建立next表
 *
 * <pre>
 *
 * next[j+1] <= next[j] + 1
 * 当j=0时，因为next[0]=-1为假想的通配符，则必有P[0]=P[next[0]]=P[-1]，
 * 因而 next[1] = next[0] + 1
 *
 * 而对于任何j都有：
 * next[j] + 1 <= next[j-1] + 1 <= ... <= next[0] + 1
 * 从而可以推出(因为每一次<=都加了1，共加了j次)：
 * next[j] < j
 *
 * 算法示意图：
 *
 *              j
 * [  P[0,j)    # P[j,m)]
 *              -----
 *                 \
 *                  这一段存在可能匹配成功的真前缀和真后缀
 * 匹配：          /
 *              -----
 *             [# P[0,t)      P[j,m)]
 *              t，t从0开始，做为P[0,j)的真前缀的第一个字符，j为P[0,j)真后缀的第一个字符
 *              j和t每一次自增，即是P[0,j)匹配的真前缀的真后缀的长度加1
 * 失配：
 *              t = next[t]，因为t>next[t]，故最终可到t=next[0]=-1，则有P[j+1] = next[0]+1 = 0
 *   [  P[0,t)  *   P[j,m)]
 *    ----------
 *    这一段是已经匹配成功的真前缀
 *
 *
 * 匹配实例演示：
 *                   j j+1
 * c  h  i  n  c  h  i  l  l  a
 * -1 0  0  0  0  1  2           -> next[j]
 *       t = 2
 * 因为 P[j] = P[t]，则 P[j+1] = t+1 = 2+1 = 3;
 *
 * 失配实例演示：
 *                      j j+1
 * c  h  i  n  c  h  i  l  l  a
 * -1 0  0  0  0  1  2  3        -> next[j]
 *          t = 3
 * 因为 l = P[j] != P[3] = n，则t = next[3] = 0，
 * 接着 l = P[j] != P[0] = c，则t = next[0] =-1，
 * 接着 t < 0，故next[j+1] = t+1 = -1+1 = 0
 *
 * </pre>
 *
 * @param P: Pattern，模式字符，即待匹配的字符
 * @return
 * @retval None
 */
int* build_next(char* P)
{
    int m = str_len(P);
    int* next = new int[m];
    int t = next[0] = -1;  // 将P[-1]当作通配符

    int j = 0;
    while(j < m-1)
    {
        // t < 0 即是P[-1]通配符处发生匹配
        if(t < 0 || P[j] == P[t])   // 匹配
            next[++j] = ++t;        // 从next[1]开始建表，因为next[0]一开始就赋值为-1了
        else                        // 失配
            t = next[t];
    }
    return next;
}

/*!
 * @brief 建立next表改进版
 *
 * <pre>
 *
 * 改进版：
 * 设P与T进行匹配，且匹配到了T[i]处
 *
 * 情况一：接连好几个字符相同
 *     j j+1
 * [0  0  0  0  0  0  1]
 * -1 -1                   -> next[j]
 *  t t+1
 * 若P[j] = P[t] 且 P[j+1] = P[t+1]，则next[j+1] = next[t+1] = -1；
 *
 * 同理一直推下去，可知前6个0的next均为-1；
 * 这样，若T[i]与P[j+1]失配，可以让P直接从头开始比较，
 * P[j+1]左侧的相同的0无需再比较（比较也肯定失配）。
 *
 *
 * 情况二：普通情况
 *              j j+1
 * [a  b  c  *  a  b  #]
 * -1  0  0     0  1        -> next[]
 * -1  0  0    -1  0        -> next_improved[]
 *  t t+1
 *
 * 若P[j] = P[t] 且 P[j+1] = P[t+1]，则next[j+1] = next[t+1] = 0；
 *
 * 按原来算法，若T[i]与P[j+1]失配，
 * 接着，应该让T[i]与 P[next[j+1]] = P[t+1] 比较
 *
 * 按照改进算法，若T[i]与P[j+1]失配，
 * 接着，直接让T[i]与 P[next[j+1] = P[0] 比较，
 * 因为既然T[i] != P[j+1]，也就有T[i] != P[t+1]，再比较T[i]与P[t+1]肯定也是失配
 * 可以这样来理解：j+1指向处于P中的自相似的子串"ab"，第一个子串失配了，另一个子串也必然失配。
 *
 * </pre>
 *
 * @param P: Pattern，模式字符，即待匹配的字符
 * @return
 * @retval None
 */
int* build_next_improved(char* P)
{
    int m = str_len(P);
    int* next = new int[m];
    int t = next[0] = -1;  // 将P[-1]当作通配符

    // 改进版
    int j = 0;
    while(j < m-1)
    {
        // t < 0 即是P[-1]通配符处发生匹配
        if(t < 0 || P[j] == P[t])   // 匹配
        {
            j++; t++;
            next[j] = (P[j]!=P[t] ? t : next[t]);
        }
        else                        // 失配
            t = next[t];
    }
    return next;
}


/*!
 * @brief BM匹配算法
 *
 * <pre>
 * BM算法：首次失配的概率越大，性能优势越明显；适合大字符表。
 * 时间复杂度：
 * len(P) = m , len(T) = n
 * O(n/m) <= BC <= O(n*m)
 * O(n/m) <= BC+GS <= O(n+m)
 *
 * 从右向左，对字符串进行比对。
 *               i           i+j
 * Text: ------ [           ] X [*****]----------
 * Pattern:     [           ] Y [*****]
 *                            j: 失配点
 * bc表：
 *      失配之处为“教训”，要想匹配成功，下一次比对的Pattern字符应当为Text中失配字符。
 *
 * gs表：
 *      失配之处为“经验”，与KMP类似，借助模式字符串的自相似性。
 *
 * </pre>
 *
 * @param P: Pattern，模式字符，即待匹配的字符
 * @param T: Text，文本字符
 * @return
 * @retval None
 */
int match_bm_bc(char* P, char* T)
{
    int n = str_len(T);
    int m = str_len(P);
    int i,j;
    int* bc = build_bc(P);

    i = 0;
    while(i <= n-m)
    {
        for (j = m-1; j >= 0; j--)
        {
            if (P[j] != T[i + j])
            {
                // 右移j-bc['x'] 或 1
                i += ((j > bc[(unsigned int)P[j]]) ? (j - bc[(unsigned int)P[j]]) : 1);
                break;
            }
        }

        if (j < 0)
            break;
    }

    delete[] bc;
    return i;
}

/*!
 * @brief BM+GS匹配算法
 *
 * 用gs表代替bc的情况3
 *
 * @param P: Pattern，模式字符，即待匹配的字符
 * @param T: Text，文本字符
 * @return
 * @retval None
 */
int match_bm_bcgs(char* P, char* T)
{
    int n = str_len(T);
    int m = str_len(P);
    int i,j;
    int* bc = build_bc(P);
    int* gs = build_gs(P);

    i = 0;
    while(i <= n-m)
    {
        for (j = m-1; j >= 0; j--)
        {
            if (P[j] != T[i + j])
            {
                // 右移j-bc['x'] 或 gs[j]
                i += ((j > bc[(unsigned int)P[j]]) ? (j - bc[(unsigned int)P[j]]) : gs[j]);
                break;
            }
        }

        if (j <= 0)
            break;
    }

    delete[] bc;
    delete[] gs;
    return i;
}

/*!
 * @brief 建立bc表(bad-character)
 *
 * <pre>
 *               i           i+j
 * Text: ------ [           ] X [*****]----------
 *              |           |
 *              |           | j: 失配点
 * Pattern:     [           ] Y [*****]
 *              |           |
 *              |     [     ] X [           ]
 *                            t = bc['X']
 *              P在P[j]处失配，若要在T[i+j]处成功匹配，则P中应该也有一个字符X；
 *              故可以直接右移 j-bc['X'] 重新进行比较（bc['X']表示字符X在P中的下标）。
 * 特殊情况1：P中有多个字符X时，取下标最大的字符X（即P中在t右侧的子串，不能再有字符X）
 * 特殊情况2：P中没有字符X时，取bc['X']=-1（类似的，-1为假想的通配符位置，同时，P中在t右侧的子串中，必定没有字符X）
 * 特殊情况3：bc['X'] > j 时（即X在Y的右侧），则只需向右移1个字符，不需要向左移；
 *            因为在 i 左侧的位置，都已经排除了，不可能发生成功的匹配；
 *            且若有多个字符X时，在j左侧也可能有X（但下标不是最大的），故只能向右移一个字符。
 * 总结：
 *      情况1,2：右移j-bc['X']， 则i = i+j-bc['X']，情况2即为i = i+j+1
 *      情况3：  右移1
 *
 * </pre>
 *
 * @param P: Pattern，模式字符，即待匹配的字符
 * @return
 * @retval None
 */
int* build_bc(char* P)
{
    // char类型最多0xFF个
    int* bc = new int[256];

    for (int k = 0; k < 256; k++)
        bc[k] = -1;
    for (int m = str_len(P), j = 0; j < m; j++)
        bc[(unsigned int)P[j]] = j;     // 覆盖刷新字符P[j]的出现位置记录，即重复的字符，下标必定是最大的
                                        // 且没有的字符均为-1
    return bc;
}

/*!
 * @brief 建立gs表(good suffix)
 *
 * <pre>
 *
 * 在不确定P中失配点j左侧有没有字符X时，才用gs表（即bc表的情况三）
 *               i           i+j
 * Text: ------ [           ] X [abcde]----------
 *              |           |
 *              |           | j: 失配点
 * Pattern:     [           ] Y [abcde]
 *              |           |     \
 *              |           |      good suffix为P的子串(若有多个good suffix，取使gs[j]最小的，即k最大的)
 *              |           | k   /
 * Pattern:     |     [     ] # [abcde      ]
 *                           gs[j] = j-k && P[gs[j]]！= 'Y'
 *
 *                                   h (good suffix为P的前缀)
 * Pattern:                       [cde                  ]
 *                                   gs[j] = len(P) - h
 * P在P[j]处失配，则i直接向右移gs[j]距离。
 *
 *
 * (1) gs为子串和前缀时的区别：
 * Text:    -----------------X--------------
 *                       |<-- r1 -->|    => 子串与后缀匹配
 *                 i     |   j      |
 * Pattern: [abc   #   abc X * X  abc]
 *             |           k        |
 *             |<------- r2 ------->|    => 前缀与后缀匹配
 *          在 P[j] = * 处失配时，向右移r1；当然，会不会漏掉 P[k] = X 的对齐位置呢？不会，因为若要在 P[k] 处成功匹配
 *                                         所有字符串，则 P[k] 与 P[j] 之间必定含有子串 abc，那么 r1 距离的起点就应
 *                                         该在 P[k] 与 P[j] 之间
 *          在 P[i] = # 处失配时，向右移r2；
 *
 *
 * (2) 由ss计算gs：
 *     j，ss[j] = 4
 * [abcd        abcd]
 * ss[j]：即在P中与P后缀相同，且以P[j]为未字符的子串(或前缀)的长度
 *
 * (2.1)若存在为前缀的good suffix，必有 ss[j]=j+1, ss[i]=i+1：
 *  0 i  j        k  h
 * [abcabc        abcabc]
 *               [abcabc        abcabc]
 *                  [abcabc        abcabc]
 * 在[0,k)之间发生失配时，均可以右移gs[x] = Len(P)-ss[j] = Len(P)-(j+1)
 * 在[k,h)之间发生失配时，均可以右移gs[x] = Len(P)-ss[i] = Len(P)-(i+1)
 * 其中有：k = Len(P) - (j+1)
 *         h = Len(P) - (i+1)
 *
 * (2.2)若存在为子中的good suffix，必有ss[j] < j+1：
 *  0     j         i: 失配点
 * [    abc          abc]
 *             [abcd        abcd]
 * 在i失配，则右移gs[i] = Len(P) - (j+1), i = Len(P) - ss[j] - 1
 * ss[j] = 0       : i = Len(P) - ss[j] - 1 = max-index
 * 0 < ss[j] < j+1 : i = Len(P) - ss[j] - 1
 *
 *
 * (3) 示例：
 *  0  1  2  3  4  5  6  7  => index
 *  非 曰 静 也 善 故 静 也
 *  A  B  C  D  E  F  C  D
 *  0  0  0  2  0  0  0  8  => ss
 *  8  8  8  8  8  4  8  1  => gs
 *
 *  A  B  A  B  x  y  z  A  B  A  B
 *  0  2  0  4  0  0  0  0  2  0  11 => ss
 *  7  7  7  7  7  7  7  9  2 11  1  => gs
 *
 * </pre>
 *
 * @param P: Pattern，模式字符，即待匹配的字符
 * @return
 * @retval None
 */
int* build_gs(char* P)
{
    int m = str_len(P);
    int* gs = new int[m];
    int* ss = new int[m];

#if(0)
    // build ss，蛮力计算 O(m^2)
    for (int k = m-1; k >= 0; k--)
    {
        int j = k;
        for (int n = m-1; n >= 0; n--)
        {
            if(P[n] != P[j])
            {
                // P的子串和后缀相等
                ss[k] = k-j;
                break;
            }
            if (--j < 0)
            {
                // P的前缀和后缀相等
                ss[k] = k-j;
                break;
            }
        }
    }
#else
    // 优化算法 O(m)
    ss[m-1] = m;        //对最后一个字符而言，与之匹配的最长后缀就是整个P串
    for (int lo = m - 1, hi = m - 1, j = lo - 1; j >= 0; j --)
    {
        if (( lo < j) &&
            (ss[m - (hi-j+1)] <= j - lo))
            //情况一
            ss[j] =  ss[m - (hi-j+1)];    // 利用此前已计算出的ss[]
        else
        {
            //情况二
            hi = j;
            lo = (lo < hi) ? lo : hi;
            while ((0 <= lo) &&
                   (P[lo] == P[m - (hi-lo+1)]))
                lo--;                       // 逐个对比处位于(lo, hi]前端的字符
            ss[j] = hi - lo;
        }
    }
#endif

    // build gs
    for (int k = 0; k < m; k ++)
        gs[k] = m;
    for (int i = 0, k = m-1; k >= 0; k--)
    {
        // (2.1)的情况
        // 因为k是倒序遍历，所在先遇到的是较长的前缀，因而先计算ss的也是P中较前面的字符
        if (ss[k] == k + 1)
        {
            while (i < m-k-1)
                gs[i++] = m-(k+1);
        }
    }
    for (int k = 0; k < m-1; k++)
        gs[m-ss[k]-1] = m-k-1;  // (2.2)的情况，不会影响(2.1)情况中计算的值

    delete[] ss;
    return gs;
}

} /* dsa */

#endif /* ifndef _STRING_H */
