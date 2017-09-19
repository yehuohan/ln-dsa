

//============================================================================//
/*
Divide and Conquer: 减而治之
    大规模问题分成两个子问题：两个子问题规模相当
 */
//============================================================================//


#include <iostream>


// 求解区间a[lo, hi]的和
int sum(int a[], int lo, int hi)
{
    int sum = 0;
    for(int k = lo; k <= hi; k++)
    {
        sum += a[k];
    }
    return sum;
}

int sum_dc(int a[], int lo, int hi)
{
    if(lo == hi) return a[lo];
    int mi = (lo + hi) / 2;
    return (sum_dc(a, lo ,mi) + sum_dc(a, mi+1, hi));
    // sum_dc(a, lo, mi)   : 子问题之一，求前半段区间之和
    // sum_dc(a, mi+1, hi) : 子问题之二，求后半段区间之和
}

int main()
{
    int a[1000];
    for(int k = 0; k < 1000; k ++)
    {
        a[k] = k;
    }

    int s1 = sum(a, 0, 1000);
    int s2 = sum_dc(a, 0, 1000);

    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
}
