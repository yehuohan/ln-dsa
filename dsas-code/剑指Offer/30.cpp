
#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;

class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
#if 0
        // 蛮力法，将相邻的正数相加，相邻的负数相加，求连续子数组的最大和
        std::vector<int> vec;
        int sum = array[0];
        for (int k = 1; k < array.size(); k ++)
        {
            if (array[k-1] * array[k] > 0)
            {
                sum += array[k];
                if (k == array.size() - 1)
                    vec.push_back(sum);
            }
            else
            {
                vec.push_back(sum);
                sum = array[k];
            }
        }

        if (vec.size() == 1)
        {
            if (vec[0] > 0)
                return vec[0];
            else
                return *std::max_element(array.begin(), array.end());
        }
        if (vec.size() == 2) return std::max(vec[0], vec[1]);

        int s = (vec[0] > 0) ? 0 : 1;
        int max = vec[s];
        int cur_sum = vec[s];
        for (int k = s; k < vec.size()-2; k += 2)
        {
            sum = cur_sum + vec[k+1] + vec[k+2];
            if (sum > cur_sum && sum > vec[k+2])
            {
                cur_sum = sum;
                if (cur_sum > max) max = cur_sum;
            }
            else
            {
                if (cur_sum > max) max = cur_sum;
                cur_sum = vec[k+2];
                if (cur_sum > max) max = cur_sum;
            }
        }
        return max;
#else
        // 动态规化
        // f(n)：以a[n]为未尾元素的子数组的和的最大值
        // f(n) = max(f(n-1) + a[n], a[n])
        int res = array[0]; // 记录当前所有子数组的和的最大值
        int max = array[0]; // 包含array[i]连接数组最大值
        for (int k = 1; k < array.size(); k ++)
        {
            max = std::max(max+array[k], array[k]);
            res = std::max(max, res);
        }
        return res;
#endif
    }
};

int main()
{
    int a[] = {6, -3, -2, 7, -15, 1, 2, 3};
    std::vector<int> vec(a, a+8);
    Solution su;
    std::cout << su.FindGreatestSumOfSubArray(vec);
}
