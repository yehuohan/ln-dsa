
#include <iostream>
#include <cstring>
#include <vector>
using std::string;

static int __ = [](){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return 0;
}();

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1 || s.length() <= numRows)
            return s;

        std::vector<std::string> grid(numRows, "");
        int index = 0;
        bool flg = true;
        for (int i = 0; i < s.length(); i ++)
        {
            grid[index].push_back(s[i]);
            if (index == 0) flg = true;
            if (index == numRows - 1) flg = false;
            (flg) ? (index++) : (index--);
        }
        std::string rs("");
        for (std::string &str:grid)
            rs += str;
        return rs;
    }
};


int main(void)
{
    Solution su;
    std::string rs = su.convert("PAYPALISHIRING", 3);
    std::cout << rs << std::endl;
    
    return 0;
}
