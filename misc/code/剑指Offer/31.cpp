
#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;

class Solution {
public:
    int NumberOf1Between1AndN_Solution(int n)
    {
        if (n == 0) return 0;
        if (n < 10) return 1;
#if 0
        // 利用已经计算的数据
        std::vector<int> vec(n+1, 0);
        vec[1] = 1;
        int cnt = 1;
        for (int k = 10; k <= n; k ++)
        {
            vec[k] = vec[k/10] + vec[k%10];
            cnt += vec[k];
        }
        return cnt;
#else
        // 个位：每10个数出现1次1
        // 十位：每100个数出现10次1
        // 百位：每1000个数出现100次1
        int cnt = 0;
        for (int k = 1; k <= n; k *= 10)
        {
            // k表示当前分析的是哪一个数位
            int div = k * 10;
            cnt += k * (n / div) + std::min(std::max(n % div - k + 1, 0), k);
        }
        return cnt;
#endif
    }
};

int main()
{
    Solution su;
    std::cout << su.NumberOf1Between1AndN_Solution(132);
}
