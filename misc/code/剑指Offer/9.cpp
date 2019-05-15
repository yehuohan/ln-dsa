
#include <iostream>

class Solution {
public:
    int jumpFloorII(int number) {

        // 仿照跳台阶分析
        // f(n) = f(n-1) + f(n-2) + ... + f(n-n)
        //      = f(n-1) + f(n-2) + ... + f(1) + f(0)
        // f(n-1) = f(n-2) + f(n-3) + ... + f(0)
        // 则有：f(n) = f(n-1) + f(n-1)
        // 其中：f(0) = 1

        if (number == 0) return 1;
        int sum = 1;
        for (int k = 1; k < number; k ++)
        {
            sum *= 2;
        }
        return sum;
    }
};


int main()
{
    Solution su;
    std::cout << su.jumpFloorII(3);
}
