
#include <iostream>
#include <vector>

class Solution {
public:
    int Fibonacci(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        int f0, f1, fn;
        int cnt = 0;
        f0 = 0;
        f1 = 1;
        cnt ++;
        while (++cnt <= n)
        {
            fn = f0 + f1;
            f0 = f1;
            f1 = fn;
        }
        return fn;
    }
};

int main()
{
    Solution su;
    std::cout << su.Fibonacci(2);
}
