
#include <iostream>

class Solution {
public:
    int jumpFloor(int number) {
        // 本质上也是斐波那契数列
        
        // 直接找规律
        // 1: 1                             1
        // 2: 2 , 1+1                       2
        // 3: 1+2, 2+1, 1+1+1               3
        // 4: 1+2+1, 1+1+1+1, 2+2           5
        // 5: 1+2+2, 1+1+1+2, 1+1+1+1+1     8

        // 使用 递归思想 推导
        // 对于f(n)
        // 第一跳是1阶，则剩下f(n-1)种跳法
        // 第一跳是2阶，则剩下f(n-2)种跳法
        // 故f(n) = f(n-1) + f(n-2)
        
        if (number == 1) return 1;
        if (number == 2) return 2;
        int f1 = 1, f2 = 2, fn;
        int cnt = 2;
        while (cnt < number)
        {
            cnt ++;
            fn = f1 + f2;
            f1 = f2;
            f2 = fn;
        }
        return fn;
    }
};

int main()
{
    Solution su;
    std::cout << su.jumpFloor(4);
}
