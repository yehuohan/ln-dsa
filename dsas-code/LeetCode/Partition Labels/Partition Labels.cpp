
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> partitionLabels(string S) {
        std::vector<int> vi;
#if(1)
        // 记录每个字母的最大的下标
        std::vector<int> pos(26, 0);
        for (unsigned int k = 0; k < S.size(); ++ k)
            pos[S[k]-'a'] = k;
        int is=0, ie=-1;
        for (int k = 0; k < S.size(); ++ k)
        {
            if (pos[S[k]-'a'] > ie) ie = pos[S[k]-'a'];
            if (k == ie)
            {
                vi.push_back(ie-is+1);
                is = k+1;
            }
        }
#else
        std::vector<std::string> vs;
        for (char c:S)
        {
            bool flg = false;
            unsigned int i;
            for (i = 0; i < vs.size(); i ++)
            {
                if (std::string::npos != vs[i].find(c))
                {
                    flg = true;
                    break;
                }
            }
            vs.push_back(std::string(""));
            vs[vs.size()-1] += c;
            if (flg)
            {
                int size = vs.size();
                for (int j = i + 1; j < size; j ++)
                    vs[i] += vs[j];
                for (int j = i + 1; j < size; j ++)
                    vs.pop_back();
            }
        }
        for (auto it:vs)
            vi.push_back(it.size());
#endif
        return vi;
    }
};

int main(void)
{
    Solution su;
    std::vector<int> vi = su.partitionLabels("ababcbacadefegdehijhklij");
    for (auto k:vi)
        std::cout << k << std::endl;
    return 0;
}
