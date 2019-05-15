
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <ctime>

#define CORE_NUM    2

/** 运行一个占空比循环 */
inline void one_loop(const int busy_time, const int idle_time)
{
    clock_t s = std::clock();
    while (((double(std::clock() - s)) / CLOCKS_PER_SEC*1000.0f) < busy_time)
        ;
    std::this_thread::sleep_for(std::chrono::milliseconds(idle_time));
}

/** 持续运行一个占空比 */
void run_loop_duty(const int duty)
{
    float d = float(duty) / 100.0f;
    int busy_time = 100 * d;
    int idle_time = 100 * (1.0f-d);
    for (;;)
        one_loop(busy_time, idle_time);
}

/** 设置直线CPU占用率 */
void set_cpu_duty(int duty)
{
    std::thread* th[CORE_NUM];
    for (int k = 0; k < CORE_NUM; k ++)
    {
        th[k] = new std::thread(run_loop_duty, duty);
        th[k]->detach();
    }
}

/** 持续运行一个占空比 */
void run_loop_sin()
{
    const double Pi = 3.14159265;
    const int I     = 100;          // 占空比周期ms
    const int T     = 20 * 1000;    // 正弦周期ms
    const int A     = I / 3;        // 正弦幅值
    const int num   = T / I;
    int sin_duty[num];
    for (int k = 0; k < num; k ++)
        sin_duty[k] = I/2 + A*std::sin(k * 2*Pi / num);

    int x = 0;
    for (;;)
    {
        x = x % num;
        one_loop(sin_duty[x], I - sin_duty[x]);
        x ++;
    }
}

/** 设置正弦CPU占用率 */
void set_cpu_sin()
{
    std::thread* th[CORE_NUM];
    for (int k = 0; k < CORE_NUM; k ++)
    {
        th[k] = new std::thread(run_loop_sin);
        th[k]->detach();
    }
}

int main()
{
    //set_cpu_duty(50);
    set_cpu_sin();

    for (;;);

    return 0;
}

