
#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    bool judge(std::vector<int> s, int l, int r)
    {
        /* 递归思想
        判断一段序列是否为BST合法后序序列
          D
         / \
        L   R
        对于后序：LRD
        根据L<D<R，找到L和R的范围，则L和R也是BST合法后序序列
        */
        if (l >= r) return true;
        int mi = r;
        // 保证D<R
        while (l < mi && s[mi-1] > s[r])
            mi--;
        // 保证L<D
        for (int k = l; k < mi; k ++)
            if (s[k] > s[r])
                return false;

        return judge(s, l, mi-1) && judge(s, mi, r-1);
    }
    bool VerifySquenceOfBST(vector<int> sequence) {
        if (!sequence.size()) return false;
        return judge(sequence, 0, sequence.size() - 1);
    }
};

int main()
{
    int a[] = {5,4,3,2,1};
    std::vector<int> s(a, a+5);
    Solution su;
    std::cout << su.VerifySquenceOfBST(s); 
}
