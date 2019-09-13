
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using std::string;
using std::vector;

class Solution {
public:
    vector<int> FindNumbersWithSum(vector<int> array,int sum) {
        std::vector<int> vec;
        if (array.size() < 2) return vec;
        int lo = 0, hi = array.size() - 1;
        while (lo < hi)
        {
            if (array[lo] + array[hi] > sum)
                hi --;
            else if (array[lo] + array[hi] < sum)
                lo ++;
            else
            {
#if 1
                // a + b = sum
                // 当a b越接近，a*b越大，反之a*b越小
                vec.push_back(array[lo]);
                vec.push_back(array[hi]);
                break;
#else
                if (vec.empty())
                {
                    vec.push_back(array[lo]);
                    vec.push_back(array[hi]);
                }
                else if (array[lo] * array[hi] < vec[0] * vec[1])
                {
                    vec[0] = array[lo];
                    vec[1] = array[hi];
                }
                lo ++;
                hi --;
            }
#endif
        }
        return vec;
    }
};

int main()
{
    int a[] = {1,2,4,7,11,15};
    std::vector<int> vec(a, a + 6);
    Solution su;
    for (auto& it:su.FindNumbersWithSum(vec, 15))
        std::cout << it << ',';


}
