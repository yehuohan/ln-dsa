
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
    bool is_subtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if (!pRoot2) return true;
        if (!pRoot1) return false;

        if (pRoot1->val == pRoot2->val)
            return (this->is_subtree(pRoot1->left, pRoot2->left)
                    && this->is_subtree(pRoot1->right, pRoot2->right));
        else
            return false;
    }
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if (!pRoot1 || !pRoot2)
            return false;
        return (this->is_subtree(pRoot1, pRoot2)
                || this->HasSubtree(pRoot1->left, pRoot2)
                || this->HasSubtree(pRoot1->right, pRoot2));
    }
};


int main()
{

}
