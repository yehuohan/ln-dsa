
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using std::string;
using std::vector;

class Solution {
public:
    // 最大堆
    std::priority_queue<int, std::vector<int>, std::less<int>> pl;
    // 最小堆
    std::priority_queue<int, std::vector<int>, std::greater<int>> pr;
    void Insert(int num)
    {
        // 蛮力法：用插入排序维持有序性
        // 高效法：用两个优先级队列实现
        if (pl.empty() || num <= pl.top()) pl.push(num);
        else pr.push(num);
        if (pl.size() == pr.size() + 2)
        {
            pr.push(pl.top());
            pl.pop();
        }
        else if (pl.size() == pr.size() - 1)
        {
            pl.push(pr.top());
            pr.pop();
        }
    }

    double GetMedian()
    {
        return (pl.size() == pr.size()) ? ((pl.top() + pr.top()) / 2.0) : pl.top();
    }

};

int main()
{

}
