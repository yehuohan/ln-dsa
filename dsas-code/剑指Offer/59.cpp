
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <stack>
using std::string;
using std::vector;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};

class Solution {
public:
    vector<vector<int> > Print(TreeNode* pRoot) {
        // 利用栈的 后进先出 特性
        std::vector<std::vector<int>> arrays;
        std::vector<int> vec;
        std::stack<TreeNode*> s, r;

        if (!pRoot) return arrays;

        s.push(pRoot);
        while (!s.empty() || !r.empty())
        {
            while (!s.empty())
            {
                TreeNode* p = s.top(); s.pop();

                if (p)
                {
                    vec.push_back(p->val);
                    // 从左向右
                    r.push(p->left); r.push(p->right);
                }
            }
            if (!vec.empty())
            {
                arrays.push_back(vec);
                vec.clear();
            }

            while (!r.empty())
            {
                TreeNode* p = r.top(); r.pop();

                if (p)
                {
                    vec.push_back(p->val);
                    // 从右向左
                    s.push(p->right); s.push(p->left);
                }
            }
            if (!vec.empty())
            {
                arrays.push_back(vec);
                vec.clear();
            }
        }
        return arrays;
    }
    
};

int main()
{

}
