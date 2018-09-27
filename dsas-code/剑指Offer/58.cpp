
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
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
    bool isSymmetrical(TreeNode* pRoot)
    {
        if (!pRoot) return true;

        return sym_root(pRoot->left, pRoot->right);
    }
    bool sym_root(TreeNode* pl, TreeNode* pr)
    {
        if (!pl && !pr) return true;
        if ((pl && !pr) || (!pl && pr)) return false;
        if (pl->val != pr->val) return false;
        return sym_root(pl->right, pr->left)
            && sym_root(pl->left, pr->right);
    }
};

int main()
{

}
