
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using std::string;
using std::vector;

class Solution {
public:
    vector<int> multiply(const vector<int>& A) {
        /*
        矩阵中第行的乘积
B0      1   A1  A2 ... An-1
B1      A0  1   A2 ... An-1
B2      A0  A1  1  ... An-1
...
Bn-2    A0  A1  ... 1  An-1
Bn-1    A0  A1  ... An-2  1
         */
        if (A.empty()) return std::vector<int>();
        std::vector<int> b(A.size());

        // 先计算下三角中每行的乘积
        b[0] = 1;
        for (int k = 1; k < b.size(); k ++)
        {
            b[k] = b[k-1] * A[k-1];
        }

        // 再计算上三角中每行的乘积，即得到矩阵每行的乘积
        int tmp = 1;
        for (int k = b.size() - 2; k >= 0; k --)
        {
            tmp *= A[k+1];
            b[k] *= tmp;
        }
        return b;
    }
};

int main()
{

}
