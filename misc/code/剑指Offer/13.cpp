
#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;

class Solution {
public:
    void reOrderArray(vector<int> &array) {
#if 0
        // 空间换时间
        std::vector<int> vec(array);
        array.clear();
        for (int k = 0; k < vec.size(); k ++)
            if (vec[k] & 0x1u)
                array.push_back(vec[k]);
        for (int k = 0; k < vec.size(); k ++)
            if (!(vec[k] & 0x1u))
                array.push_back(vec[k]);
#else
        // 时间换空间
        for (int i = 0; i < array.size(); i ++)
        {
            for (int j = array.size() - 1; j > i; j --)
            {
                if (array[j]&0x1u && !(array[j-1]&0x1u))
                    std::swap(array[j], array[j-1]);
            }
        }
#endif
    }
};

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> vec(a, a+7);
    Solution su;
    su.reOrderArray(vec);
    for (auto& it:vec)
        std::cout << it << "  ";
}
