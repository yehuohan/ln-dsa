
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using std::string;
using std::vector;

class Solution {
public:
    vector<vector<int> > FindContinuousSequence(int sum) {
        std::vector<std::vector<int>> arrays;
        std::vector<int> vec;
        std::queue<int> q;
        int s = 0;
        int i = 0;
        for (int k = 1; k < sum; k ++)
        {
            s += k;
            std::cout << s << std::endl;
            vec.push_back(k);
            while (s > sum)
                s -= vec[i++];
            if (s == sum)
                arrays.push_back(std::vector<int>(vec.begin() + i, vec.end()));
        }
        return arrays;
    }
};

int main()
{
    Solution su;
    su.FindContinuousSequence(9);
}
