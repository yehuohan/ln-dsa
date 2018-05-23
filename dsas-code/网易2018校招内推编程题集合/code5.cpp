
/*
[编程题] 独立的小易

时间限制：1秒
空间限制：32768K

小易为了向他的父母表现他已经长大独立了,他决定搬出去自己居住一段时间。一个人生活增加了许多花费: 小易每天必须吃一个水果并且需要每天支付x元的房屋租金。当前小易手中已经有f个水果和d元钱,小易也能去商店购买一些水果,商店每个水果售卖p元。小易为了表现他独立生活的能力,希望能独立生活的时间越长越好,小易希望你来帮他计算一下他最多能独立生活多少天。

输入描述:
输入包括一行,四个整数x, f, d, p(1 ≤ x,f,d,p ≤ 2 * 10^9),以空格分割

输出描述:
输出一个整数, 表示小易最多能独立生活多少天。

输入例子1:
3 5 100 10

输出例子1:
11
*/

#include <iostream>

int live_days(int x, int f, int d, int p)
{
    int days = 0;
    if (d >= f * x)
    {
        days += f;
        d -= f * x;
    }
    else
    {
        days = d / x;
        d %= x;
    }
    days += (d / (x + p));
    return days;
}

int main(int argc, char *argv[])
{
    int x, f, d, p;
    std::cin >> x >> f >> d >> p;

    std::cout << live_days(x, f, d, p);
    return 0;
}
