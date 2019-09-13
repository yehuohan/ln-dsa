
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <bitset>
using std::string;
using std::vector;

class Solution {
public:
    bool IsContinuous( vector<int> numbers ) {
        /*
        1、排序 
        2、计算所有相邻数字间隔总数 
        3、计算0的个数 
        4、如果2、3相等，就是顺子 
        5、如果出现对子，则不是顺子
         */

        /*
         或者必须满足两个条件
        1. 除0外没有重复的数
        2. max - min < 5 
         */
        if (numbers.empty()) return false;
        std::bitset<15> bs;
        bs.reset();
        int max = -INT_MAX, min = INT_MAX;
        for (int k = 0; k < numbers.size(); k ++)
        {
            if (numbers[k] == 0)
                continue;
            if (bs.test(numbers[k])) return false;
            bs.set(numbers[k]);
            if (numbers[k] < min) min = numbers[k];
            if (numbers[k] > max) max = numbers[k];
            if (max - min >= 5) return false;
        }
        return true;
    }
};

int main()
{
    int a[] = {1, 3, 0, 5, 0};
    std::vector<int> vec(a, a + 5);
    Solution su;
    std::cout << su.IsContinuous(vec);
}
