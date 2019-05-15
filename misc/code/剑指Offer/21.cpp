
#include <iostream>
#include <vector>
#include <stack>
using std::vector;

class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        // 栈混洗
        std::stack<int> s;
        int i = 0;
        for (int k = 0; k < pushV.size(); k ++)
        {
            s.push(pushV[k]);
            while (!s.empty() && s.top() == popV[i])
            {
                i ++;
                s.pop();
            }
        }
        return s.empty();
    }
};

int main()
{

}
