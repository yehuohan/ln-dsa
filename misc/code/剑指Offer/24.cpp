
#include <iostream>
#include <vector>
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
    void add_path(std::vector<std::vector<int>>& vec,
            std::vector<int> path,
            TreeNode* root,
            int expectNumber)
    {
        // 深度优先搜索
        if (root)
        {
            path.push_back(root->val);
            if (expectNumber == root->val
                && !root->left
                && !root->right)
                vec.push_back(path);
            add_path(vec, path, root->left, expectNumber - root->val);
            add_path(vec, path, root->right, expectNumber - root->val);
        }
        else
        {
           path.pop_back();
        }
    }

    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
        std::vector<std::vector<int>> vec(0, std::vector<int>(0));
        std::vector<int> path;
        add_path(vec, path, root, expectNumber);
        return vec;
    }
};

int main()
{

}
