
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
    int TreeDepth(TreeNode* pRoot)
    {
        if (!pRoot) return 0;
        return 1 + std::max(TreeDepth(pRoot->left), TreeDepth(pRoot->right));
    }
};

int main()
{

}
