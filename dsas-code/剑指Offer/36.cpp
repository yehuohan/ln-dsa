
#include <iostream>
#include <vector>
#include <unordered_map>
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
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        if (!pHead1 || !pHead2) return NULL;

#if 1
        // 使用Hash
        std::unordered_map<ListNode*, int> mp;

        ListNode* p = pHead1;
        while (p)
        {
            mp.insert(std::pair<ListNode*, int>(p, 1));
            p = p->next;
        }
        p = pHead2;
        while (p)
        {
            if (mp.count(p))
                return p;
            p = p->next;
        }
        return NULL;
#else
        // 用两个指针扫描"两个链表"，最终两个指针到达 NULL 或者到达公共结点。 
        ListNode* p1 = pHead1;
        ListNode* p2 = pHead2;
        while (p1 != p2)
        {
            p1 = p1 ? p1->next : pHead2;
            p2 = p2 ? p2->next : pHead1;
        }
        return p1;
#endif
    }
};

int main()
{

}
