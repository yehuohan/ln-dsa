
#include <stdio.h>

#define   	SetBit(reg,bit)      	((reg) |= (1 << (bit)))
#define     BitIsHigh(reg,bit)    	(0 != ((reg) & (1 << (bit))))

int rangeBitwiseAnd(int m, int n)
{
	if (n == 0 || m == 0 || m == n)
		return m;

	int ret = 0;
	int k = 31;
	while (k >= 0)
	{
		if (BitIsHigh(n, k) && BitIsHigh(m, k))
			SetBit(ret, k);
		else if (BitIsHigh(n, k) != BitIsHigh(m, k))
			break;
		k--;
	}

	return ret;
}


int main()
{
    printf("%d\n", rangeBitwiseAnd(5, 7));
    return 0;
}
