
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using std::string;
using std::vector;

class Solution {
public:
    void calc_permutation(std::vector<string>& vec, std::string& s, int pos)
    {
        // 所谓的回溯法，按照排列组合的方法思考
        // 字符串s：abcde
        // s[0] 与0后的任何字符swap，即0处有n个选择
        // s[1] 与1后的任何字符swap，即1处有n-1个选择
        // 直到将s[n] swap后,即可得到一个排列

        // pos: 排序字符串的结束位置
        if (pos == s.size() - 1)
            vec.push_back(s);
        else
        {
            for (int k = pos; k < s.size(); k ++)
            {
                if (!(pos != k && s[pos] == s[k]))          // 保证要swap的字符不相同
                {
                    std::swap(s[pos], s[k]);
                    calc_permutation(vec, s, pos+1);
                    std::swap(s[pos], s[k]);                // 再次swap，防止影响下一次计算
                }
            }
        }
    }

    vector<string> Permutation(string str) {
        std::vector<string> vec;
        std::string s(str);
        calc_permutation(vec, s, 0);

        std::sort(vec.begin(), vec.end());                  // 牛客网答案需要按顺序

        return vec;
    }
};

int main()
{
    std::string str("abc");
    Solution su;
    for (auto& it:su.Permutation(str))
        std::cout << it << std::endl;

}
