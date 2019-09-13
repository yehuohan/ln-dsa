
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <bitset>
using std::string;
using std::vector;

class Solution {
public:
    // Parameters:
    //        numbers:     an array of integers
    //        length:      the length of array numbers
    //        duplication: (Output) the duplicated number in the array number
    // Return value:       true if the input is valid, and there are some duplications in the array number
    //                     otherwise false
    bool duplicate(int numbers[], int length, int* duplication) {
#if 0
        if (length == 0) return false;
        std::bitset<100000> bs;
        bs.reset();

        for (int k = 0; k < length; k ++)
        {
            if (bs.test(numbers[k]))
            {
                *duplication = numbers[k];
                return true;
            }
            else
                bs.set(numbers[k]);
        }
        return false;
#else
        if (length == 0) return false;
        for (int k = 0; k < length; k ++)
        {
            // 数字范围在0~n-1
            int index = numbers[k];
            if (numbers[index % length] >= length)
            {
                *duplication = index - length;
                return true;
            }
            numbers[index % length] += length;
        }
        return false;
#endif
    }
};

int main()
{

}
