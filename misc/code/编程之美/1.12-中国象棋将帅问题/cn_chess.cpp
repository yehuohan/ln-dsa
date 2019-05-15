
#include <iostream>

/*!
 * 只用一个变量，且不用位操作。
 *
 * 原版   循环81次
 * 改进版 循环54次
 */
void print_pos1()
{
#define COL(n) ((n)/3)
    unsigned char k = 81;
    while (k--)
    {
        // k从81递减
        // k/9 和 k%9 的范围均为 [0,8]
#if 0
        // 原版
        if (COL(k/9) == COL(k%9))
            continue;
        std::cout << "A = " << (int)(k/9+1) << ", B = " << (k%9+1) << std::endl;
#else
        // 改进版
        // 0 3 6
        // 1 4 7
        // 2 5 8
        // k/9 : 8 8 8 8 8 8 8 8 8 7 7 7
        // k%9 : 8 7 6 5 4 3 2 1 0 8 7 6...
        // k/9 = 8 且 k%9 = 8 时， k直接减到5
        // k/9 = 5 且 k%9 = 5 时， k直接减到2
        // k/9 = 2 且 k%9 = 2 时， k直接减到0
        if (COL(k/9) == COL(k%9))
            k -= 2;
        else
            std::cout << "A = " << (int)(k/9+1) << ", B = " << (k%9+1) << std::endl;
#endif
    }
#undef COL
}

/*!
 *
 * 通过struct bit输出。
 * 循环9x6 = 54次。
 *
 */
void print_pos2()
{
    typedef struct Pos
    {
        unsigned char a:4;
        unsigned char b:4;
    }Pos;

#define COL(n) ((n)/3)
    Pos pos;
    for (pos.a = 0; pos.a <= 8; pos.a++)
        for (pos.b = (COL(pos.a)+1)*3; pos.b < (COL(pos.a)+3)*3; pos.b ++)
            std::cout << "A = " << (int)(pos.a+1)
                      << ", B = " << (int)(pos.b%9+1) << std::endl;
#undef COL
}

int main()
{
    print_pos1();
    //print_pos2();

    return 0;
}
