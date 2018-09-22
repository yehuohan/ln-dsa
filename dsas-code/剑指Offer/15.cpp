
#include <iostream>
#include <algorithm>

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        if (!pHead) return NULL;

        ListNode* head = pHead;
        ListNode* t    = pHead;
        ListNode* p    = pHead;
        while (p)
        {
            t = p;
            p = p->next;

            t->next = head;
            head = t;
        }
        pHead->next = NULL;

        return head;
    }
};

int main()
{
    ListNode p1(1), p2(2), p3(3), p4(4), p5(5);
    p1.next = &p2;
    p2.next = &p3;
    p3.next = &p4;
    p4.next = &p5;

    Solution su;
    ListNode* p = su.ReverseList(&p1);
    while (p)
    {
        std::cout << p->val << " ";
        p = p->next;
    }
}
