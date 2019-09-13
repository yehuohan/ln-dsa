
#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;

class Solution {
public:
    int GetUglyNumber_Solution(int index) {
        //  丑数：p = 2^x * 3^y * 5^z
        /*
维护三个队列：
（1）丑数数组： 1
乘以2的队列：2
乘以3的队列：3
乘以5的队列：5
选择三个队列头最小的数2加入丑数数组，同时将该最小的数乘以2,3,5放入三个队列；
（2）丑数数组：1,2
乘以2的队列：4
乘以3的队列：3，6
乘以5的队列：5，10
选择三个队列头最小的数3加入丑数数组，同时将该最小的数乘以2,3,5放入三个队列；
（3）丑数数组：1,2,3
乘以2的队列：4,6
乘以3的队列：6,9
乘以5的队列：5,10,15
选择三个队列头里最小的数4加入丑数数组，同时将该最小的数乘以2,3,5放入三个队列；
（4）丑数数组：1,2,3,4
乘以2的队列：6，8
乘以3的队列：6,9,12
乘以5的队列：5,10,15,20
选择三个队列头里最小的数5加入丑数数组，同时将该最小的数乘以2,3,5放入三个队列；
（5）丑数数组：1,2,3,4,5
乘以2的队列：6,8,10，
乘以3的队列：6,9,12,15
乘以5的队列：10,15,20,25
选择三个队列头里最小的数6加入丑数数组，但我们发现，有两个队列头都为6，所以我们弹出两个队列头，同时将12,18,30放入三个队列；
         */

        if (index < 7) return index;

        int p2 = 0, p3 = 0, p5 = 0, num = 1;
        std::vector<int> vec;
        vec.push_back(num);
        while (vec.size() < index)
        {
            num = std::min(vec[p2] * 2, std::min(vec[p3] * 3, vec[p5] * 5));
            if (vec[p2] * 2 == num) p2 ++;
            if (vec[p3] * 3 == num) p3 ++;
            if (vec[p5] * 5 == num) p5 ++;
            vec.push_back(num);
        }
        return num;
    }
};

int main()
{
    Solution su;
    std::cout << su.GetUglyNumber_Solution(8);
}
