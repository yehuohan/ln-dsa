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

namespace dsa
{

/*!
 * @addtogroup LString
 *
 * @{
 */


/*!
 * @brief
 *
 * 串
 *
 * 相等：
 *      S[0,n) = T[0,m)
 *      长度相等，且对应的字符相同
 * 子串：
 *      substr(i,k) = S[i, i+k), 0<= i < n, 0 <= k
 *      从S[i]起的连续k个字符
 * 前缀：
 *      prifix(k) = substr(0,k) = S[0,k), 0 <= k <= n
 *      最靠前k个字符
 * 后缀：
 *      suffix(k) = substr(n-k, k) = S[n-k, n), 0 <= k <= n
 *      最靠后的k个字符
 * 空串：
 *      S[0, n=0)
 *
 */
class String
{
    int     length();
    char    at();
    String  substr(int i, int k);
    String  prifix(int k);
    String  suffix(int k);
    String  join();
    bool    equal();
    char    index();
};

int     strlen(const char*);

int     match_bf1(char* P, char* T);
int     match_bf2(char* P, char* T);

int     match_kmp(char*, char*);
int*    build_next(char*);
int*    build_next_improved(char*);

/*! @} */


/*!
 * @brief 获取字符串长度
 *
 * @param str: 字符串，以'\0'结尾
 * @return
 * @retval None
 */
int strlen(const char* str)
{
    int len = 0;
    while(*str++ != '\0')
    {
        len ++;
    }
    return len;
}


/*!
 * @brief  蛮力匹配(Brute-force-1)
 *
 * @param P: Pattern，模式字符，即待匹配的字符
 * @param T: Text，文本字符
 * @return
 * @retval None
 */
int match_bf1(char* P, char* T)
{
    int n = strlen(T), i = 0;
    int m = strlen(P), j = 0;

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
 * @param P: Pattern，模式字符，即待匹配的字符
 * @param T: Text，文本字符
 * @return
 * @retval None
 */
int match_bf2(char* P, char* T)
{
    int n = strlen(T), i = 0;
    int m = strlen(P), j;

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
 * 示例：
 * 0  1  2  3  4  5  6  7  8  9  -> 字符的下标j
 * c  h  i  n  c  h  i  l  l  a
 * -1 0  0  0  0  1  2  3  0  0  -> next[j]
 *
 *                             失配点
 *                           /
 * Text    :  c h i n c h i *
 * Pattern :  c h i n c h i l l a
 * next[j] :          c h i n c h i l l a
 * 如果在 l 处失配，说明 l 前的 chi 是匹配的，
 * 故pattern最开始的 chi 则不需要再次比较。
 *
 *
 * Next[j]的建立：
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
 * N(P,j) = { 0 <= t < j | P[0,t) == P[j-t, j) }
 * 即：
 *      在P的前缀P[0,j)中，P[0,j)的真前缀P[0,t)和真后缀P[j-t,j)匹配的长度，就是next[j]
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
    int* next = build_next(P);
    int n = strlen(T), i = 0;
    int m = strlen(P), j = 0;

    while(j < m && i < n)
    {
        // j = next[j] = -1: 说明在P的首字符发生失配
        // P[-1]相当一个通配符，只要 j=-1<0，则必定匹配
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
 * 当j=0时，因为next[0]=-1相当于通配符，则必有P[0]=P[next[0]]=P[-1]，
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
    int m = strlen(P);
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
 *
 * 情况一：连接好向个字符相同
 *     j j+1    i
 * [0  0  0  0  0  0  1]
 * -1 -1                   -> next[j]
 *  t t+1
 * 若P[j] = P[t] 且 P[j+1] = P[t+1]，则next[j+1] = next[t+1] = -1；
 *
 * 同理一直推下去，可知前6个0的next均为-1；
 * 这样，当在i处，P与T失配时，可以让P直接从头开始比较，
 * i前面的几个相两只0无需再比较（比较也肯定失配）。
 *
 *
 * 情况二：普通情况
 *              j j+1
 * [a  b  c  *  a  b  #]
 * -1  0  0     0  1        -> next[]
 * -1  0  0    -1  0        -> next_improved[]
 *  t t+1
 *
 * 若P[j] = P[j] 且 P[j+1] = P[t+1]，则next[j+1] = next[t+1] = 0；
 *
 * 按原来算法，若T[i]与P[j+1]失配，
 * 接着，应该让T[i]与 P[next[j+1]] = P[t+1] 比较
 *
 * 按照改进算法，若T[i]与P[j+1]失配，
 * 接着，直接让T[i]与 P[next[j+1] = P[0] 比较，
 * 因为既然T[i] != P[j+1]，也就有T[i] != P[t+1]，再比较T[i]与P[t+1]肯定也是失配
 *
 * </pre>
 *
 * @param P: Pattern，模式字符，即待匹配的字符
 * @return
 * @retval None
 */
int* build_next_improved(char* P)
{
    int m = strlen(P);
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

} /* dsa */

#endif /* ifndef _STRING_H */
