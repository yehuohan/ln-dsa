
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using std::string;
using std::vector;

class Solution {
public:
    vector<int> maxInWindows(const vector<int>& num, unsigned int size)
    {
        if (size == 1) return num;
        std::vector<int> vec;
        if (num.empty() || size == 0) return vec;

        // 用双端队列实现单调险列
        std::deque<int> q;
        for (unsigned int k = 0; k < num.size(); k ++)
        {
            while (!q.empty() && num[q.back()] <= num[k])
                q.pop_back();
            while (!q.empty() && k - q.front() >= size)
                q.pop_front();
            q.push_back(k);
            if (k+1 >= size)
                vec.push_back(num[q.front()]);
        }
        return vec;
    }
};

int main()
{
    int a[] = { 2,3,4,2,6,2,5,1 };
    std::vector<int> vec(a, a+ 8);
    Solution su;
    for (auto& it:su.maxInWindows(vec, 3))
        std::cout << it << ',';
}
