
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using std::string;
using std::vector;

class Solution {
public:
    int Add(int num1, int num2)
    {
        // 利用位运算做二进制加法
        return num2 ? Add(num1^num2, (num1&num2)<<1) : num1;
    }
};

int main()
{
    Solution su;
    std::cout << su.Add(4, 5);
}
