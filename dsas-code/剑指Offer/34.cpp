
#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>
using std::vector;
using std::string;

class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        if (str.empty()) return -1;

        // 先统计所有字符出现次数，再返回出现次数为1的第一个字符
        int cnt[256];
        std::memset(cnt, 0, 256*sizeof(int));
        for (int k = 0; k < str.size(); k ++)
        {
            cnt[str[k]] ++;
        }

        for (int k = 0; k < str.size(); k ++)
        {
            if (cnt[str[k]] == 1)
            {
                return k;
            }
        }
        return -1;
    }
};

int main()
{
    Solution su;
    std::cout << su.FirstNotRepeatingChar("aabcc");
}
