
#include <iostream>
#include <vector>
#include <queue>
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
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        // 广度优先搜索
        std::queue<TreeNode*> q;
        std::vector<int> vec;
        TreeNode* node;
        q.push(root);
        while (!q.empty())
        {
            node = q.front();
            q.pop();
            if (node)
            {
                q.push(node->left);
                q.push(node->right);
                vec.push_back(node->val);
            }
        }
        return vec;
    }
};

int main()
{

}
