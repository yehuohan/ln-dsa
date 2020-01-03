
//==============================================================================
/*!
 * @file usestl.h
 * @brief simple usage of stl.
 *
 * @date 20180526
 * @version
 * @author yehuohan, <yehuohan@gmail.com>
 * @copyright
 */
//==============================================================================


#ifndef _USE_STL
#define _USE_STL

#include <iostream>

#define PutTitle(str)     std::cout << str
#define PutContent(str)   std::cout << "    " << str


// Container
extern void container_vector(void);
extern void container_list(void);
extern void container_hash_map(void);
extern void container_hash_set(void);
extern void container_iterator(void);
extern void container_bitset(void);
extern void container_priority_queue(void);
extern void container_deque(void);

// Algorithm
extern void algorithm_maxmin(void);
extern void algorithm_sort(void);
extern void algorithm_heap(void);

// Thread
extern void thread_thread(void);

// Atomic
extern void atomic_atomic(void);

#endif /* ifndef _USE_STL */
