
#include "usestl.h"


using stl_func = void(*)(void);

/*!
 * @brief execute function
 *
 */
void exec_stl(stl_func sf)
{
    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    sf();
}


int main()//int argc, char *argv[])
{
#if 0
    exec_stl(container_vector);
    exec_stl(container_list);
    exec_stl(container_iterator);
    exec_stl(container_hash_set);
    exec_stl(container_hash_map);
#endif

#if 0
    exec_stl(algorithm_maxmin);
    exec_stl(algorithm_sort);
#endif

#if 1
    exec_stl(thread_thread);
#endif

    return 0;
}
