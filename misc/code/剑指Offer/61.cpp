
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
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

#if 1
    // 迭代法，先序遍历 序列化和反序列化
    char* Serialize(TreeNode *root)
    {
        if (!root) return NULL;
        std::stack<TreeNode*> s;
        std::string str;

        TreeNode* p = root;
        s.push(p);
        while (!s.empty())
        {
            p = s.top(); s.pop();
            while (p)
            {
                str += std::to_string(p->val);
                str += ',';
                s.push(p->right);
                p = p->left;
            }
            str += '#';
        }

        char* chs = new char[str.length() + 1];
        int k;
        for (k = 0; k < str.length(); k ++)
            chs[k] = str[k];
        chs[k] = '\0';
        return chs;
    }

    // Deserialize没写出来
    TreeNode* Deserialize(char *str)
    {
        if (!str) return NULL;
        std::stack<TreeNode*> s;
        TreeNode* r = NULL;

        char* p = str;
        int val = 0;
        int cnt = 0;        // counter for '#'
        int flg = 0;        // 0 for left, 1 for right
        while (*p != '\0')
        {
            if ('0' <= *p && *p <= '9')
            {
                val = val * 10 + (*p - '0');
                cnt = 0;
            }
            else if (*p == ',')
            {
                if (cnt)
                    ;
                else
                    ;
                val = 0;
            }
            else if (*p == '#')
                cnt ++;
            p++;
        }

        return r;
    }

#else
    // 递归法，先序遍历 序列化和反序列化
    char* Serialize(TreeNode *root)
    {
        if (!root) return NULL;

        std::string str;
        Serialize(root, str);

        char* chs = new char[str.length() + 1];
        int k;
        for (k = 0; k < str.length(); k ++)
            chs[k] = str[k];
        chs[k] = '\0';
        return chs;
    }
    void Serialize(TreeNode* root, std::string& str)
    {
        // 先序遍历 序列化
        if (!root)
        {
            str += '#';
            return;
        }

        str += std::to_string(root->val);
        str += ',';
        Serialize(root->left, str);
        Serialize(root->right, str);
    }

    TreeNode* Deserialize(char *str)
    {
        if (!str)
            return NULL;
        return Deserialize(&str);
    }

    TreeNode* Deserialize(char** str)
    {
        // 先序遍历 反序列化
        if (**str == '#')
        {
            ++(*str);
            return NULL;
        }

        int val = 0;
        while (**str != '\0' && **str != ',')
        {
            val = val * 10 + ((**str) - '0');
            ++(*str);
        }

        TreeNode* root = new TreeNode(val);
        if (**str == '\0')
            return root;
        else
            ++(*str);
        root->left = Deserialize(str);
        root->right = Deserialize(str);
        return root;
    }
#endif
};

int main()
{

}
