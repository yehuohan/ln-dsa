
#include "usestl.h"
#include <vector>
#include <iterator>

void container_iterator(void)
{
    PutTitle("\nContainer iterator begin.\n");

    int arr[] = {3, 2, 1, 5, 4};
    std::vector<int> vec(arr, arr+5);

    // index
    PutTitle("use index:\n");
    for (int k = 0; k < vec.size(); k ++)
        PutContent(vec[k]);
    // std::next
    PutTitle("\nuse next:\n");
    for (std::vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter = std::next(iter, 1))
        PutContent(*iter);
    // iterator++
    PutTitle("\nuse ++:\n");
    for (std::vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter++)
        PutContent(*iter);
    // auto && iterator++
    PutTitle("\nuse auto\n");
    for (auto iter = vec.begin(); iter != vec.end(); iter++)
        PutContent(*iter);
    PutTitle("\n");
    for (const auto& it:vec)
        PutContent(it);
    PutTitle("\n");
    for (auto it:vec)
        PutContent(it);

    PutTitle("\nContainer iterator end.\n");
}
