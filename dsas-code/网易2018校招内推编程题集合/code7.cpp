
/*
[编程题] 疯狂队列

时间限制：1秒
空间限制：32768K

小易老师是非常严厉的,它会要求所有学生在进入教室前都排成一列,并且他要求学生按照身高不递减的顺序排列。有一次,n个学生在列队的时候,小易老师正好去卫生间了。学生们终于有机会反击了,于是学生们决定来一次疯狂的队列,他们定义一个队列的疯狂值为每对相邻排列学生身高差的绝对值总和。由于按照身高顺序排列的队列的疯狂值是最小的,他们当然决定按照疯狂值最大的顺序来进行列队。现在给出n个学生的身高,请计算出这些学生列队的最大可能的疯狂值。小易老师回来一定会气得半死。

输入描述:
输入包括两行,第一行一个整数n(1 ≤ n ≤ 50),表示学生的人数
第二行为n个整数h[i](1 ≤ h[i] ≤ 1000),表示每个学生的身高

输出描述:
输出一个整数,表示n个学生列队可以获得的最大的疯狂值。
如样例所示:
当队列排列顺序是: 25-10-40-5-25, 身高差绝对值的总和为15+30+35+20=100。
这是最大的疯狂值了。

输入例子1:
5
5 10 25 40 25

输出例子1:
100
*/

#include <iostream>
#include <vector>
#include <algorithm>

/*!
 * @brief crazy_queue
 *
 * 先对height排序，
 * 然后累加abs(max-min)，累加流程如下：
 *    -------------
 *   /    -----   \
 *  /   /      \   \
 * h1, h2, h3, h4, h5
 *     \          /
 *      ----------
 * 当累加到剩最后中间的h3和h4，累加abs(h1 - h3)，而不是abs(h3 - h4)
 *
 * @param None
 * @return
 * @retval None
 */
int crazy_queue(int* h, int n)
{
    int val = 0;
    std::vector<int> hei(h, h+n);
    // sort
    std::sort(hei.begin(), hei.end());

    int lo = 0, hi = n - 1;
    int idx = lo;
    while(lo <= idx && idx <= hi)
    {
        // sum
        if (idx == lo)
        {
            if (idx + 1 == hi)
                val += std::abs(hei[0] - hei[hi]);
            else
                val += std::abs(hei[idx] - hei[hi]);
            idx = hi;
            lo ++;
        }
        else if (idx == hi)
        {
            if (lo + 1 == idx)
                val += std::abs(hei[0] - hei[lo]);
            else
                val += std::abs(hei[idx] - hei[lo]);
            idx = lo;
            hi --;
        }
    }
    return val;
}

int main(int argc, char *argv[])
{
    int n = 5;
    int h[] = {5, 10, 25, 40, 25};
    //std::cin >> n;
    //int* h = new int[n];
    //for (int k = 0; k < n; k ++)
    //    std::cin >> h[k];
    std::cout << crazy_queue(h, n);
    //delete[] h;

    return 0;
}
