
#include <iostream>
#include <stack>

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
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        if (!pRootOfTree)
            return NULL;

        TreeNode* head = NULL;
        TreeNode* p = pRootOfTree;
        TreeNode* pp = NULL;
        std::stack<TreeNode*> s;

        // head
        while (p)
        {
            head = p;
            p = p->left;
        }

        p = pRootOfTree;
        while (true)
        {
            while (p)
            {
                s.push(p);
                p = p->left;
            }
            if (s.empty()) break;
            else
            {
                p = s.top(); s.pop();

                // 按 中序遍历顺序 连接
                p->left = pp;
                if (pp) pp->right = p;
                pp = p;

                p = p->right;
            }
        }
        return head;
    }
};

int main()
{

}
