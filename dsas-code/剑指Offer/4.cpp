
#include <iostream>
#include <vector>
using std::vector;

/**
 * Definition for binary tree
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        TreeNode* root = new TreeNode(0);

        if (pre.empty()) return NULL;

        // 递归实现
        std::vector<int> left_pre, left_vin, right_pre, right_vin;
        int mi = 0;
        for (int k = 0; k < vin.size(); k ++)
        {
            if (pre[0] == vin[k])
            {
                mi = k;
                break;
            }

        }
        for (int k = 0; k < vin.size(); k ++)
        {
            if (k < mi)
            {
                left_vin.push_back(vin[k]);
                left_pre.push_back(pre[k+1]);
            }
            else if (k > mi)
            {
                right_vin.push_back(vin[k]);
                right_pre.push_back(pre[k]);
            }
        }

        root->val = pre[0];
        root->left = this->reConstructBinaryTree(left_pre, left_vin);
        root->right = this->reConstructBinaryTree(right_pre, right_vin);
        return root;
    }
};

int main()
{
    Solution su;
    return 0;
}
