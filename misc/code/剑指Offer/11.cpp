
#include <iostream>


class Solution {
public:
    int  NumberOf1(int n) {
        int cnt = 0;
        while (n)
        {
            cnt ++;
            n &= (n-1);
        }
        return cnt;
    }
};

int main()
{
    Solution su;
    std::cout << su.NumberOf1(10);
}
