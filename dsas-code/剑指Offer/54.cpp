
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using std::string;
using std::vector;


class Solution
{
public:
    std::string s;
    int chs[256] = {0};
  //Insert one char from stringstream
    void Insert(char ch)
    {
        s.push_back(ch);
        chs[ch] ++;
    }
  //return the first appearence once char in current stringstream
    char FirstAppearingOnce()
    {
        for (int k = 0; k < s.size(); k ++)
        {
            if (chs[s[k]] == 1)
                return s[k];
        }
        return '#';
    }

};

int main()
{

}
