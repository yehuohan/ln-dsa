
/*

[编程题] 操作序列

时间限制：2秒
空间限制：32768K

小易有一个长度为n的整数序列,a_1,...,a_n。然后考虑在一个空序列b上进行n次以下操作:
1、将a_i放入b序列的末尾
2、逆置b序列
小易需要你计算输出操作n次之后的b序列。

输入描述:
输入包括两行,第一行包括一个整数n(2 ≤ n ≤ 2*10^5),即序列的长度。
第二行包括n个整数a_i(1 ≤ a_i ≤ 10^9),即序列a中的每个整数,以空格分割。

输出描述:
在一行中输出操作n次之后的b序列,以空格分割,行末无空格。

输入例子1:
4
1 2 3 4

输出例子1:
4 2 1 3
*/

#include <iostream>

void do_operation(int* a, int* b, int n)
{
    if (n == 1)
    {
        b[0] = a[0];
        return;
    }

    // 奇偶区分
    int idx = n / 2;
    if (!(n & 1))
        idx --;
    int idx_right = idx;
    int idx_left = idx - 1;

    b[idx_right++] = a[0];
    bool reverse = true;
    for (int k = 1; k < n ; k ++)
    {
        if (reverse)
            b[idx_right++] = a[k];
        else
            b[idx_left--] = a[k];
        reverse = !reverse;
    }

    // 偶数反转
    if (!(n & 1))
    {
        for (int k = 0; k < n / 2; k ++)
        {
            b[k] ^= b[n - k - 1];
            b[n - k - 1] ^= b[k];
            b[k] ^= b[n - k -1];
            //t = b[k];
            //b[k] = b[n - k - 1];
            //b[n - k - 1] = t;
        }
    }
}

int main(int argc, char *argv[])
{
    int n = 4;
    int a[4] = {1, 2, 3, 4};
    int b[4] = {0};
    //std::cin >> n;
    //a = new int[n];
    //b = new int[n];
    //for (int k = 0; k < n; k ++)
    //    std::cin >> a[k];
    do_operation(&a[0], &b[0], n);
    for (int k = 0; k < n; k ++)
    {
        std::cout << b[k];
        if (k < n - 1)
            std::cout << ' ';
    }
    //delete[] a;
    //delete[] b;

    return 0;
}
