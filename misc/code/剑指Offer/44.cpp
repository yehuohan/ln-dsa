
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using std::string;
using std::vector;

class Solution {
public:
    string ReverseSentence(string str) {
        std::vector<std::string> vec;
        std::string s;
        for (auto& ch:str)
        {
            if (ch == ' ')
            {
                vec.push_back(s);
                s.clear();
            }
            else
                s.push_back(ch);
        }
        vec.push_back(s);

        for (int i = 0, j = vec.size() - 1; i < j; i ++, j --)
            std::swap(vec[i], vec[j]);

        s.clear();
        for (int k = 0; k < vec.size(); k ++)
        {
            s += vec[k];
            if ( k != vec.size() - 1)
                s += ' ';
        }
        return s;
    }
};

int main()
{
    Solution su;
    std::cout << su.ReverseSentence(std::string("I am a student."));
}
