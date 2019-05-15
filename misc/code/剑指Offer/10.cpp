
#include <iostream>

class Solution {
public:
    int rectCover(int number) {
        // 还是 斐波那契

        /*
        f(n)：2*n的大矩形

        竖摆：  #---------  还剩2*(n-1)大矩形
                #---------

        横摆：  ##--------  还剩2*(n-2)大矩形 
                ##--------
        */

        if (number == 0) return 0;
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
    std::cout << su.rectCover(10);
}
