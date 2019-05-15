
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using std::vector;

class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        std::vector<int> vec;
        if (input.size() == 0
            || input.size() < k
            || k == 0)
            return vec;

#if 0
        // 通过栈来维护取小的K个数
        std::stack<int> s;
        for (auto& it:input)
        {
            if (vec.empty())
                vec.push_back(it);
            else
            {
                while (!vec.empty() && vec.back() > it)
                {
                    s.push(vec.back());
                    vec.pop_back();
                }
                if (vec.size() < k)
                    vec.push_back(it);
                while (vec.size() < k && !s.empty())
                {
                    vec.push_back(s.top());
                    s.pop();
                }
            }
        }
#else
        // 利用堆
        std::make_heap(input.begin(), input.end(), [](int a, int b){return a>b;});
        int cnt = 0;
        while (cnt < k)
        {
            std::pop_heap(input.begin(), input.end()-cnt, [](int a, int b){return a>b;});
            cnt ++;
            vec.push_back(input[input.size() - cnt]);
        }
#endif
        return vec;
    }
};

int main()
{
    int a[] = {4,5,1,6,2,7,3,8};
    std::vector<int> vec(a, a+8);
    Solution su;
    for (auto& it:su.GetLeastNumbers_Solution(vec, 4))
        std::cout << it << ',';
}
