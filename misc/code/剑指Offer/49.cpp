
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using std::string;
using std::vector;

class Solution {
public:
    int StrToInt(string str) {
        if (str.empty()) return 0;
        int flg = str[0] == '-' ? -1 : 1;
        int sum = 0;
        for (int k = 0; k < str.size(); k ++)
        {
            if ('0' <= str[k] && str[k] <= '9')
            {
                sum *= 10;
                sum += str[k] - '0';
            }
            else if (str[k] == '-' || str[k] == '+')
                ;
            else
                return 0;
        }
        return sum*flg;
    }
};

int main()
{

}
