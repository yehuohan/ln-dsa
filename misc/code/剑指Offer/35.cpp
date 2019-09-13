
#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    int cnt;
    int InversePairs(vector<int> data) {
#define N 1000000007
        if (data.size() <= 1) return 0;
        cnt = 0;

#if 0
        // 插入排序
        int cnt = 0;
        for (int k = 1; k < data.size(); k ++)
        {
            int tmp = data[k];
            int i = k;
            while (i > 0 && tmp < data[i-1])
            {
                data[i] = data[i-1];
                i --;
                cnt ++;
                cnt %= N;
            }
            data[i] = tmp;
        }
        return cnt;
#else
        // 归并排序
        merge_sort(data, 0, data.size() - 1);
        return cnt;
#endif
    }

    void merge_sort(std::vector<int>& data, int lo, int hi)
    {
        if (lo >= hi)
            return;
        int mi = (hi + lo) / 2;
        merge_sort(data, lo, mi);
        merge_sort(data, mi + 1, hi);

        merge(data, lo, mi, hi);
    }

    void merge(std::vector<int>& data, int lo, int mi, int hi)
    {
        std::vector<int> tmp(hi - lo + 1);
        int i = lo, j = mi + 1, k = 0;
        while (i <= mi && j <= hi)
        {
            if (data[i] < data[j]) tmp[k++] = data[i++];
            else
            {
                tmp[k++] = data[j++];
                cnt += mi - i + 1;      // 统计逆序对
                                        // 进行归并时，左右两部分均是有序的
                                        // 从data[i]到data[mi]的数均大于data[j]
                cnt %= N;
            }
        }
        while (i <= mi) tmp[k++] = data[i++];
        while (j <= hi) tmp[k++] = data[j++];
        for (int k = 0; k < tmp.size(); k ++)
            data[lo + k] = tmp[k];
    }
};

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 0};
    std::vector<int> vec(a, a+8);
    Solution su;
    std::cout << su.InversePairs(vec);
}
