
#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    int GetNumberOfK(vector<int> data ,int k) {
#if 0
        // O(n) 蛮力法
        int cnt = 0;
        for (auto& it:data)
            if (it == k) cnt ++;
        return cnt;
#else
        // 二分查找
        return bin_search(data, k+0.5) - bin_search(data, k-0.5);
#endif
    }
    int bin_search(vector<int>& data, float k)
    {
        int lo = 0, hi = data.size() - 1;
        while (lo <= hi)
        {
            int mi = (hi - lo) / 2 + lo;
            if (data[mi] < k)
                lo = mi + 1;
            else if (data[mi] > k)
                hi = hi - 1;
        }
        return lo;
    }
};

int main()
{

}
