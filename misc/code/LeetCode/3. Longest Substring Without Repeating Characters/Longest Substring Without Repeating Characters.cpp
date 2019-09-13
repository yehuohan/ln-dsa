
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.empty()) return 0;

        std::vector<int> pos(256, -1);
        int maxlen = 1;
        int ss = 0; // 子串的起始下标
        for (int k = 0; k < s.size(); ++k)
        {
            // 如果pos中存在s[k]，则ss指向已存在的s[k]的下一个字符
            if (pos[s[k]] >= 0)
                ss = std::max(ss, pos[s[k]]+1);
            // 记录字符s[k]
            pos[s[k]] = k;
            maxlen = std::max(maxlen, k + 1 - ss);
        }
        return maxlen;
    }
};


int main()
{
    Solution su;
    cout << su.lengthOfLongestSubstring("dvdfad");
    return 0;
}
