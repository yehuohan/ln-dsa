
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace::std;

class Solution {
public:
    string makeLargestSpecial(string S) {
#if(1)
        return dfs(S);
#else
        this->make_largest_special(S);
        return S;
#endif
    }

    // 参考[Think of it as Valid-Parentheses](https://leetcode.com/problems/special-binary-string/discuss/)
    /** 使用深度优先搜索，进行reorder */
    std::string dfs(const string& s)
    {
        // recursion base
        if (s == "10") return s;

        int cnt = 0;
        std::string str;
        std::vector<std::string> sec;
        for (char ch:s)
        {
            str += ch;
            (ch == '1') ? cnt ++ : cnt --;
            if (cnt == 0)
            {
                sec.push_back("1" + dfs(str.substr(1, str.size()-2)) + "0");
                str.clear();
            }
        }

        // reorder
        str.clear();
        std::sort(sec.begin(), sec.end(), [](std::string a, std::string b){return a>b;});
        for (auto &it:sec) str.append(it);
        return str;
    }

    /** 查找sub-special string */
    void find_sec(const string& s, std::vector<std::string>& sec)
    {
        int cnt = 0;
        std::string str("");
        for (char ch:s)
        {
            (ch == '1') ? cnt ++ : cnt --;
            str += ch;
            if (cnt == 0)
            {
                sec.push_back(str);
                str.clear();
            }
        }
    }

    /** 对sub-special string进行reorder */
    void make_largest_special(string& s)
    {
        if (s == "10") return;

        std::vector<std::string> sec;
        find_sec(s, sec);

        if (sec.size() <= 1)
        {
            std::string ss(s.substr(1, s.size()-2));
            make_largest_special(ss);
            s = "1" + ss + "0";
            return;
        }
        for (auto &it:sec) make_largest_special(it);

        std::sort(sec.begin(), sec.end(), [](std::string a, std::string b){return a>b;});
        s.clear();
        for (auto &it:sec) s.append(it);
    }
};

int main()
{
    std::string str("11011000");
    Solution su;
    std::string r = su.makeLargestSpecial(str);

    std::cout << "src: " << str << std::endl;
    std::cout << "dst: " << r << std::endl;
}
