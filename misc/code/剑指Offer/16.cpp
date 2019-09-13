
#include <iostream>

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        if (!pHead1) return pHead2;
        if (!pHead2) return pHead1;
        ListNode* h;
        ListNode* head;
        if (pHead1->val < pHead2->val)
        {
            head = pHead1;
            pHead1 = pHead1->next;
        }
        else
        {
            head = pHead2;
            pHead2 = pHead2->next;
        }
        h = head;
        while (pHead1 && pHead2)
        {
            if (pHead1->val < pHead2->val)
            {
                h->next = pHead1;
                pHead1 = pHead1->next;
                h = h->next;
            }
            else
            {
                h->next = pHead2;
                pHead2 = pHead2->next;
                h = h->next;
            }
        }
        if (pHead1)
            h->next = pHead1;
        else if (pHead2)
            h->next = pHead2;
        return head;
    }
};

int main()
{

}
