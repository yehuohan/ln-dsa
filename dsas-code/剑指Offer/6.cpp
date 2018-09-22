
#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;


class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        if (rotateArray.empty())
            return 0;
        // 蛮力法:遍历全数组

        // 二分法
        int lo = 0;
        int hi = rotateArray.size() - 1;
        while (lo < hi)
        {
            int mi = (lo + hi) / 2;
            if (rotateArray[mi] > rotateArray[hi])
                lo = mi + 1;
            else if (rotateArray[mi] == rotateArray[hi])
                hi --;
            else
                hi = mi;
        }
        return rotateArray[lo];
    }
};


int main()
{
    std::vector<int> vec;
}
