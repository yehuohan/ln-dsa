
#include <stdio.h>


int is_prime(int n)
{
    // 0~32
    if (n == 2 || n == 3 || n == 5 || n == 7 ||
        n == 11 || n == 13 || n == 17 || n == 19 ||
        n == 23 || n == 29 || n == 31)
        return 1;
    return 0;
}

int count_bits(int n)
{
    // bit32, 0~31
    int cnt = 0;
    for (int k = 0; k < 32; k ++)
        if (n & (1 << k)) cnt ++;
    return cnt;
}

int countPrimeSetBits(int L, int R) {
    int num = 0;
    for (int k = L; k <= R; k ++)
        num += is_prime(count_bits(k));
    return num;
}

int main()
{
    printf("num: %d", countPrimeSetBits(6, 10));
    
    return 0;
}
