
#include "usestl.h"
#include <thread>
#include <mutex>
#include <conio.h>

int cnt = 0;
std::mutex mtx;

void func(int k)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    mtx.lock();
    PutContent("k: " << k << "  cnt: " << cnt << std::endl);
    mtx.unlock();
    cnt ++;
}


/*!
 * @brief 线程创建
 *
 */
void thread_thread(void)
{
    PutTitle("\nThread thread begin.\n");

    std::thread* th[10];
    int k = 0;
    for (k = 0; k < 10; k ++)
    {
        th[k] = new std::thread(func, k);    // 按值传递参数k
        //th[k]->join();        // 阻塞当前线程，直至 *this 所标识的线程完成其执行。
        th[k]->detach();        // 从 thread 对象分离执行的线程，允许执行独立地持续。
    }

    while (cnt < 10);

    PutTitle("\nThread thread end.\n");
}
