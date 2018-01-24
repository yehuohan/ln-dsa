
#include <iostream>
#include <vector>
#include <algorithm>

using namespace::std;

class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        if (intervals.size() == 0)
            return 0;

        std::sort(intervals.begin(), intervals.end(),
                [](const std::vector<int> a, const std::vector<int>& b){
                    // 按右端升序，右端相同时，按左端降序
                    if (a[1] < b[1]) return true;
                    else if (a[1] == b[1] && a[0] > b[0]) return true;
                    return false;
                });

        // 一个interval最右端的两个点
        int i = intervals[0][1] - 1;
        int j = intervals[0][1];
        int res = 2;
        for (auto &it:intervals)
        {
            // 情况(1)
            if (i < it[0] && it[0] <= j)
            {
                res ++;
                i = j;
                j = it[1];
            }
            // 情况(2)
            else if (j < it[0])
            {
                res += 2;
                i = it[1] - 1;
                j = it[1];
            }
            else
            { }
        }

        return res;
    }
};


int main()
{
    vector<vector<int>> iv;
    vector<int> it(2);
    it[0] = 1; it[1] = 2; iv.push_back(it);
    it[0] = 2; it[1] = 3; iv.push_back(it);
    it[0] = 2; it[1] = 4; iv.push_back(it);
    it[0] = 4; it[1] = 5; iv.push_back(it);

    Solution su;
    int size = su.intersectionSizeTwo(iv);
    std::cout << "Size: " << size << std::endl;

    return 0;
}
