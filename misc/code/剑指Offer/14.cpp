
#include <iostream>
#include <queue>

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

class Solution {
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        ListNode* pk = pListHead;
        ListNode* p = pListHead;
        while (p)
        {
            p = p->next;
            if (k <= 0)
                pk = pk->next;
            else
                k --;
        }
        return k == 0 ? pk : NULL;
    }
};

int main()
{

}
