
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
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
    TreeNode* KthNode(TreeNode* pRoot, int k)
    {
        if (!pRoot) return NULL;
        if (k == 0) return NULL;

        std::stack<TreeNode*> s;

        TreeNode* p = pRoot;
        while (true)
        {
            while (p)
            {
                s.push(p);
                p = p->left;
            }
            if (s.empty()) break;

            p = s.top(); s.pop();
            if (--k <= 0) break;

            p = p->right;
        }
        return p;
    }
};

int main()
{

}
