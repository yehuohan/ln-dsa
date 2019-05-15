
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using std::string;
using std::vector;

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
        
    }
};

class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode)
    {
        if (!pNode) return NULL;

        // 即求二叉树节点的直接后继

        // 有右子树：pNode的中序下一个节点为 右子树最左子节点
        if (pNode->right)
        {
            pNode = pNode->right;
            while (pNode->left) pNode = pNode->left;
            return pNode;
        }
        // 没有右子树：父节点中包含当前节点的最低节点
        while (pNode->next)
        {
            if (pNode->next->left == pNode) return pNode->next;
            pNode = pNode->next;
        }
        return NULL;
    }
};

int main()
{

}
