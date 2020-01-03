
#include "usestl.h"
#include <atomic>
#include <thread>

std::atomic_flag lock = ATOMIC_FLAG_INIT;
std::atomic<int> aint;
//int aint;

void func_print(int k) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    aint ++;

    while (lock.test_and_set());
    std::cout << "thread#" << k << "$" << aint << std::endl;
    lock.clear();
}

void atomic_atomic(void) {
    PutTitle("\nAtomic atomic begin.\n");
    aint = 0;
    std::thread* ths[10];
    for (int k = 0; k < 10; k ++)
        ths[k] = new std::thread(func_print, k);
    for (int k = 0; k < 10; k ++)
        ths[k]->join();
    PutTitle("\nAtomic atomic end.\n");
}
