
#include "usestl.h"
#include <vector>
#include <algorithm>
#include <cstdlib>

/*!
 * @brief 用于make_heap的比较函数
 *
 */
int cmp_heap(int a, int b)
{
    // 最大堆
    return (a < b);
    // 最小堆
    //return (a < b);
}

/*!
 * @brief 排序算法
 *
 */
void algorithm_heap(void)
{
    PutTitle("\nAlgorithm heap cegin.\n");

    int arr[] = {2, 5, 1, 4, 3};
    int size = sizeof(arr) / sizeof(int);
    std::vector<int> vec(arr, arr + size);

    // 构建堆，不提供cmp_heap时，默认为最大堆
    std::make_heap(vec.begin(), vec.end(), cmp_heap);

    // 插入堆，将原来0~n-1个看成一个堆，将第n个插入堆中
    vec.push_back(9);
    std::push_heap(vec.begin(), vec.end(), cmp_heap);

    // 弹出堆，将0处堆顶放到最后，现将0~n-1做成一个堆
    std::pop_heap(vec.begin(), vec.end(), cmp_heap);

    // 堆排序，用sort_heap前，需要make_heap
    //std::sort_heap(vec.begin(), vec.end());

    // 输出
    PutTitle("arr:\n");
    for (int k = 0; k < size; k ++)
        PutContent(arr[k] << ' ');
    PutTitle("\nheap:\n");
    for (int k = 0; k < vec.size(); k ++)
        PutContent(vec[k] << ' ');

    PutTitle("\nAlgorithm heap end.\n");
}
