
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
    bool IsBalanced_Solution(TreeNode* pRoot) {
        // 后续遍历二叉树，遍历过程中求子树高度，判断是否平衡
#if 0
        // 递归遍历
        int dep = 0;
        return is_balanced(pRoot, dep);
#else
        // 迭代遍历（没写出来）
        std::stack<TreeNode*> s;
        std::stack<int> dep;
        TreeNode* p = pRoot;
        TreeNode* last;
        int lcnt = 0, rcnt = 0;
        while (true)
        {
            while (p)
            {
                s.push(p);
                p = p->left;
            }
            while (!s.empty())
            {
                p = s.top(); s.pop();
                if (!p->right && p->right == last)
                {
                    // visit(p)
                    if (!p->right)
                    {
                        rcnt = 0;
                    }
                    else if (p->right == last)
                    {
                        lcnt = dep.top(); dep.pop();
                        rcnt ++;
                        if (std::abs(lcnt - rcnt) > 1) return false;
                        lcnt = 1 + std::max(lcnt, rcnt);
                    }

                    last = p;
                }
                else
                {
                    dep.push(lcnt);     // 保存左子树高度
                    s.push(p);
                    p = p->right;
                    break;
                }
            }
            if (s.empty()) break;
        }

        return true;
#endif
    }

    bool is_balanced(TreeNode* root, int& dep)
    {
        if (!root) return true;

        int lcnt = 0, rcnt = 0;

        if (is_balanced(root->left, lcnt) && is_balanced(root->right, rcnt))
        {
            if (std::abs(lcnt-rcnt) > 1)
                return false;
            dep = 1 + std::max(lcnt, rcnt);
            return true;
        }
        return false;
    }
};


int main()
{

}
