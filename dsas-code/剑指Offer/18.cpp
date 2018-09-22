
#include <iostream>

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
    void Mirror(TreeNode *pRoot) {
        if (pRoot)
        {
            TreeNode* node = pRoot->left;
            pRoot->left = pRoot->right;
            pRoot->right = node;
            this->Mirror(pRoot->left);
            this->Mirror(pRoot->right);
        }
    }
};

int main()
{

}
