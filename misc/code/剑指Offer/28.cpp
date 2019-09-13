
#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        if (!numbers.size()) return 0;

        // 可能的众数
        int cnt = 0;
        int p;
        for (int k = 0; k < numbers.size(); k ++)
        {
            if (cnt == 0)
            {
                p = numbers[k];
                cnt ++;
            }
            else
                (p == numbers[k]) ?  cnt ++ : cnt --;
        }

        // 验证众数
        cnt = 0;
        for (int k = 0; k < numbers.size(); k ++)
            if (numbers[k] == p)
                cnt ++;

        return (cnt > numbers.size() / 2) ? p : 0;
    }
};

int main()
{
    int a[] = {1,2,3,2,2,2,5,4,2};
    std::vector<int> vec(a, a+9);
    Solution su;
    std::cout << su.MoreThanHalfNum_Solution(vec);

}
