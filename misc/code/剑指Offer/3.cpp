
#include <iostream>
#include <vector>
using std::vector;

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

class Solution {
public:
    std::vector<int> ar;
    vector<int> printListFromTailToHead(ListNode* head) {
        // 用Stack或Vector转移数据
#if 0
        std::vector<int> array;

        ListNode* node = head;
        while (node != NULL)
        {
            array.push_back(node->val);
            node = node->next;
        }

        std::vector<int> vec(array.size());
        for (int k = 0; k < array.size(); k ++)
            vec[k] = array[array.size() - k - 1];
        return vec;
#endif
        // 递归法
        if (head != NULL)
        {
            this->printListFromTailToHead(head->next);
            this->ar.push_back(head->val);
        }
        return this->ar;
    }
};

int main()
{

}
