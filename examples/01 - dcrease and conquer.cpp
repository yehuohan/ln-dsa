
//============================================================================//
/*
Decrease and Conquer: 减而治之
    大规模问题分成两个子问题：一个规模减小，一个为平常问题
 */
//============================================================================//


#include <iostream>

int sum(int a[], int n)
{
    int sum = 0;
    for(int k = 0; k < n; k++)
    {
        sum += a[k];
    }
    return sum;
}

int sum_dc(int a[], int n)
{
    return (n < 1) ? 0 : (sum_dc(a,n-1) + a[n-1]);
    // sum_de(a,n-1) : 子问题之一，规模减小，仍是同类问题，仍可调用自身解决
    // + a[n-1]      : 子问题这二，平常的加法问题
}

int main()
{
    int a[1000];
    for(int k = 0; k < 1000; k ++)
    {
        a[k] = k;
    }

    int s1 = sum(a, 1000);
    int s2 = sum_dc(a, 1000);

    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
}
