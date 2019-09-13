
#include <stdio.h>
#include <malloc.h>

/** 返回[0,num]的1的个数 */
int* count_bits_range(int num)
{
	int* rcb = (int*)malloc((num + 1)*sizeof(int));
    rcb[0] = 0; rcb[1] = 1;

    // k >> 1 = k / 2
    // k & 1  = k % 2
    for (int k = 2; k <= num; k ++)
        rcb[k] = rcb[k >> 1] + rcb[k & 1];
    return rcb;
}

/** 返回n的1的个数 */
int count_bits(int n)
{
    // bit32, 0~31
    int cnt = 0;
#if(1)
    while(n)
    {
        cnt ++;
        n &= (n-1);
    }
#else
    for (int k = 0; k < 32; k ++)
        if (n & (1 << k)) cnt ++;
#endif
    return cnt;
}

int is_prime(int n)
{
    // 0~32
    if (n == 2 || n == 3 || n == 5 || n == 7 ||
        n == 11 || n == 13 || n == 17 || n == 19 ||
        n == 23 || n == 29 || n == 31)
        return 1;
    return 0;
}

int countPrimeSetBits(int L, int R) {
    int num = 0;
#if(1)
    int* cb = count_bits_range(R);
    for (int k = L; k <= R; k ++)
        num += is_prime(cb[k]);
    free(cb);
#else
    for (int k = L; k <= R; k ++)
        num += is_prime(count_bits(k));
#endif
    return num;
}

int main()
{
    printf("num: %d", countPrimeSetBits(6, 10));
    
    return 0;
}
