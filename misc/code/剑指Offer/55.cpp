
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <unordered_map>
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
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
#if 0
        // 使用HashMap
        ListNode* p = pHead;
        std::unordered_map<ListNode*, int> mp;
        while (p)
        {
            if (mp.count(p))
                return p;
            mp.insert(std::pair<ListNode*, int>(p, 1));
            p = p->next;
        }
        return NULL;
#else
        if (!pHead || !pHead->next) return NULL;


        /*
        1.第一步，找环中相汇点。分别用p1，p2指向链表头部，p1每次走一步，p2每次走二步，直到p1==p2找到在环中的相汇点。
        2.第二步，找环的入口。接上步，当p1==p2时，p2所经过节点数为2x,p1所经过节点数为x,设环中有n个节点,p2比p1多走一圈有2x=n+x; n=x;可以看出p1实际走了一个环的步数，再让p2指向链表头部，p1位置不变，p1,p2每次走一步直到p1==p2; 此时p1指向环的入口。
        */
        ListNode *p1 = pHead->next, *p2 = pHead;
        while (p2 && p2->next)
        {
            p1 = p1->next;
            p2 = p2->next->next;
            if (p1 == p2)
            {
                p2 = pHead;
                while (p1 != p2)
                {
                    p1 = p1->next;
                    p2 = p2->next;
                }
                if (p1 == p2)
                    return p1;
            }
        }
        return NULL;
#endif
    }
};

int main()
{

}
