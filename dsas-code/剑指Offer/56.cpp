
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using std::string;
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
    ListNode* deleteDuplication(ListNode* pHead)
    {
        if (!pHead || !pHead->next) return pHead;

        // 递归
        // 第i个节点的next是i+1~n节点去重后的head
        // i->next = f(i+1)
        if (pHead->val == pHead->next->val)
        {
            ListNode* p = pHead->next;
            while (p && p->val == pHead->val)  // 去除重复节点
                p = p->next;
            return deleteDuplication(p);
        }
        else
        {
            pHead->next = deleteDuplication(pHead->next);
            return pHead;
        }

    }
};

int main()
{

}
