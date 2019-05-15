
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
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
            // 广度优先遍历

            std::vector<std::vector<int>> arrays;
            std::vector<int> vec;
            std::queue<TreeNode*> q;
            int cnt = 0;

            if (!pRoot) return arrays;

            q.push(pRoot);
            while (!q.empty())
            {
                if (cnt <= 0)
                {
                    cnt = q.size();
                    if (!vec.empty())
                    {
                        arrays.push_back(vec);
                        vec.clear();
                    }
                }
                if (cnt)
                    cnt --;

                TreeNode* p = q.front();
                q.pop();
                if (p)
                {
                    vec.push_back(p->val);
                    q.push(p->left);
                    q.push(p->right);
                }
            }
            return arrays;
        }
};

int main()
{

}
