
#include "usestl.h"
#include <string>
#include <vector>

#define _TO_STR(s)      (#s)
#define TO_STR(s)       _TO_STR(s)
#define EXEC_STL(sf)    exec_stl(TO_STR(sf), sf)

using stl_func = void(*)(void);
std::vector<stl_func> vfuncs;
std::vector<std::string> vnames;

/*!
 * @brief execute function
 *
 */
void exec_stl(std::string name, stl_func sf) {
    vfuncs.push_back(sf);
    vnames.push_back(name);
}


int main()//int argc, char *argv[])
{
#if 1
    EXEC_STL(container_vector);
    EXEC_STL(container_list);
    EXEC_STL(container_iterator);
    EXEC_STL(container_hash_set);
    EXEC_STL(container_hash_map);
    EXEC_STL(container_bitset);
    EXEC_STL(container_priority_queue);
    EXEC_STL(container_deque);
#endif
#if 1
    EXEC_STL(algorithm_heap);
    EXEC_STL(algorithm_maxmin);
    EXEC_STL(algorithm_sort);
#endif
#if 1
    EXEC_STL(thread_thread);
    EXEC_STL(atomic_atomic);
#endif

#if 1
    vfuncs[vfuncs.size()-1]();
#else
    while (true) {
        int ch;
        for (size_t k = 0; k < vnames.size(); k ++) {
            std::cout << k << ". " << vnames[k] << std::endl;
        }
        std::cout << "Choice: ";
        std::cin >> ch;
        if (ch < vfuncs.size())
            vfuncs[ch]();
        else
            break;
    }
#endif

    return 0;
}
