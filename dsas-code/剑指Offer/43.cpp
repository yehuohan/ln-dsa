
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using std::string;
using std::vector;

class Solution {
public:
    string LeftRotateString(string str, int n) {
        // YX = (X^T * Y^T)^T
        if (str.empty()) return "";

        int len = str.size();
        for (int i = 0, j = len - 1; i < j; i ++, j --) std::swap(str[i], str[j]);
        for (int i = 0, j = len - n - 1; i < j; i ++, j --) std::swap(str[i], str[j]);
        for (int i = len - n, j = len - 1; i < j; i ++, j --) std::swap(str[i], str[j]);
        return str;
    }
};

int main()
{
    Solution su;
    std::cout << su.LeftRotateString(std::string("abcdefg"), 2);

}
