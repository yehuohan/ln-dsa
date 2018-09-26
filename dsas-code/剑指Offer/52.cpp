
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using std::string;
using std::vector;

class Solution {
public:
    bool match(char* str, char* pattern)
    {
        // 字符串和模式串同时到达'\0'，说明两个串匹配
        if (pattern[0] == '\0' && str[0] == '\0')
            return true;

        // 模式串第1和第2个字符为'a*'形式，模式串+2
        if (pattern[0] != '\0' && pattern[1] == '*')
            if (match(str, pattern + 2))
                return true;

        // 模式串为'.'，或两个字符相同
        if ((pattern[0] == '.' && str[0]) || str[0] == pattern[0])
        {
            // 继续匹配：字符串和模式串+1
            if (match(str+1, pattern+1))
                return true;
            // 上述匹配失败且模式串第2个字符串为'*'，字符串+1
            if (pattern[1] == '*' && match(str+1, pattern))
                return true;
        }
        return false;
    }
};

int main()
{
    Solution su;
    std::cout << su.match("abcce", "a.*ce");
}
