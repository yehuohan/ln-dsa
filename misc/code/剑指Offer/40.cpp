
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using std::string;
using std::vector;

class Solution {
public:
    void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
        // 异或运算：任何一个数字异或它自己偶数次都等于0
        // 或者用 HashMap

        if (data.size() < 2)
            return;

        // val肯定是两个只出现一次数学的异或结果
        int val = data[0];
        for (int k = 1; k < data.size(); k ++)
            val ^= data[k];

        // 找到val第一个为1的位
        // 在index位，num1和num2肯定一个为1，一个为0
        int index = 0;
        while (((1 << index) & val) == 0)
        {
            index ++;
        }

        // 根据index，分成两个子数组进行异或运算
        *num1 = 0;
        *num2 = 0;
        for (int k = 0; k <data.size(); k ++)
        {
            if ((1 << index) & data[k])
                *num1 ^= data[k];
            else
                *num2 ^= data[k];
        }
    }
};

int main()
{

}
