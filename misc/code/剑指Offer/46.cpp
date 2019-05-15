
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using std::string;
using std::vector;

class Solution {
public:
    int LastRemaining_Solution(int n, int m)
    {
#if 1
        // 递归法
        // f(n) 为第n个报m的人的编号
        // f(n) = (f(n-1) + m) % n, f(1) = 0

        //if (n == 0) return -1;
        //if (n == 1) return 0;
        //else return (LastRemaining_Solution(n-1, m) + m) % n;

        // 直接计算
        int s = 0;
        for (int k = 2; k <= n; k ++)
            s = (s+m) % k;
        return s;
#else
        // 模拟法
        if (n == 0) return -1;
        std::vector<int> vec(n, 0);
        int i = -1;
        int pos = 0;
        while (n > 1)
        {
            i ++;
            if (vec[i % vec.size()] == 1) continue;
            pos ++;
            if (pos == m)
            {
                vec[i % vec.size()] = 1;
                pos = 0;
                n --;
            }
        }
        
        for (i = 0; i < vec.size(); i ++)
            if (vec[i] == 0)
                break;
        return i;
#endif
    }
};

int main()
{
    Solution su;
    std::cout << su.LastRemaining_Solution(10, 3);
}
