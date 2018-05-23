
/*

[编程题] 堆棋子

时间限制：1秒
空间限制：32768K

小易将n个棋子摆放在一张无限大的棋盘上。第i个棋子放在第x[i]行y[i]列。同一个格子允许放置多个棋子。每一次操作小易可以把一个棋子拿起并将其移动到原格子的上、下、左、右的任意一个格子中。小易想知道要让棋盘上出现有一个格子中至少有i(1 ≤ i ≤ n)个棋子所需要的最少操作次数.

输入描述:
输入包括三行,第一行一个整数n(1 ≤ n ≤ 50),表示棋子的个数
第二行为n个棋子的横坐标x[i](1 ≤ x[i] ≤ 10^9)
第三行为n个棋子的纵坐标y[i](1 ≤ y[i] ≤ 10^9)

输出描述:
输出n个整数,第i个表示棋盘上有一个格子至少有i个棋子所需要的操作数,以空格分割。行末无空格

如样例所示:
对于1个棋子: 不需要操作
对于2个棋子: 将前两个棋子放在(1, 1)中
对于3个棋子: 将前三个棋子放在(2, 1)中
对于4个棋子: 将所有棋子都放在(3, 1)中

输入例子1:
4
1 2 4 9
1 1 1 1

输出例子1:
0 1 3 10
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <limits>

typedef struct point_s
{
    int x, y;
    point_s(int _x, int _y) : x(_x), y(_y){}
}point_t;

inline int calc_dis(point_t a, point_t b)
{
    return (std::abs(a.x - b.x) + std::abs(a.y - b.y));
}

void move_chess(int* x, int* y, int* count, int n)
{
    // init
    count[0] = 0;
    std::vector<point_t> p;
    for (int k = 0; k < n; k ++)
    {
        p.push_back(point_t(x[k], y[k]));
    }

    // sort
    std::sort(p.begin(), p.end(), [](point_t a, point_t b)->bool{return a.x < b.x;});

    // calculate distance
    std::vector<int> dis;
    for (int k = 1; k < n; k ++)
    {
        dis.push_back(calc_dis(p[k - 1], p[k]));
    }

    // count moves
    for (int k = 1; k < n; k ++)
    {
        count[k] = count[k] + dis[k-1]; 
    }
}

int main(int argc, char *argv[])
{
    int n;
    int* x;
    int* y;
    std::cin >> n;
    x = new int[n];
    y = new int[n];
    for (int k = 0; k < n; k ++)
        std::cin >> x[k];
    for (int k = 0; k < n; k ++)
        std::cin >> y[k];
    int* count = new int[n];
    move_chess(x, y, count, n);
    for (int k = 0; k < n; k ++)
    {
        std::cout << count[k];
        if (k < n - 1)
            std::cout << ' ';
    }
    delete[] x;
    delete[] y;
    delete[] count;
    
    return 0;
}
