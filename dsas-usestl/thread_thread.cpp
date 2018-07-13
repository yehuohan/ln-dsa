
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
 * @brief join方式运行多线程
 *
 */
void thread_join(void)
{
    std::thread* th[10];
    int k = 0;
    for (k = 0; k < 10; k ++)
    {
        th[k] = new std::thread(func, k);    // 按值传递参数k
        //th[k]->join();          // 阻塞当前主线程，直至 *this 所标识的线程完成其执行。
                                // 当创建thread对象后立即join，效果等于顺序执行
    }
    for (k = 0; k < 10; k ++)
    {
        th[k]->join();          // 阻塞当前主线程，直至 *this 所标识的线程完成其执行。
                                // 当创建thread对象后统一join，实现多线程运行。
    }

    // 因为主线程会等join的线程结束，
    // 所以不用依靠cnt计数来判断多线程是否全部执行完毕。
    //while (cnt < 10);
}

/*!
 * @brief detach方式运行多线程
 *
 */
void thread_detach(void)
{
    std::thread* th[10];
    int k = 0;
    for (k = 0; k < 10; k ++)
    {
        th[k] = new std::thread(func, k);    // 按值传递参数k
        th[k]->detach();        // 从 thread 对象分离执行的线程，允许执行独立地持续。
    }

    // 因为主线程不会等待detach的线程结束，
    // 所以不等待cnt达到10（说明detach的线程都运行完毕），
    // 则看不到线程输出结果（因为主线程已经结束）。
    while (cnt < 10);
}


/*!
 * @brief 线程创建
 *
 */
void thread_thread(void)
{
    PutTitle("\nThread thread begin.\n");
    //thread_join();
    thread_detach();
    PutTitle("\nThread thread end.\n");
}
