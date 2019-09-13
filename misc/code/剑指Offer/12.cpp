
#include <iostream>

class Solution {
public:
    double Power(double base, int exponent) {
        // b ^ n
        // n为偶数：b^n = b^(n/2) * b^(n/2)
        // n为奇数：b^n = b^(n/2) * b^(n/2+1)

        if (exponent > 0)
        {
            if (exponent == 1)
                return base;
            else if (exponent & 0x1u)
            {
                return this->Power(base, exponent/2) * this->Power(base, exponent/2 + 1);
            }
            else
            {
                return this->Power(base, exponent/2) * this->Power(base, exponent/2);
            }
        }
        else if (exponent == 0)
            return 1;
        else
            return (1 / this->Power(base, -exponent));
    }
};

int main()
{
    Solution su;
    std::cout << su.Power(1.38, 10);

}
