
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using std::string;
using std::vector;

class Solution {
public:
    int Sum_Solution(int n) {
        //(n > 0) && (n += Sum_Solution(n-1));
        //return n;

        // 1+2+3+...+n = n(n+1) / 2
        bool a[n][n+1];
        return sizeof(a) >> 1;
    }
};

int main()
{
    Solution su;
    std::cout << su.Sum_Solution(5);
}
