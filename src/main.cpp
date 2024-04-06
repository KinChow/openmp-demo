/*
 * @Author: Zhou Zijian 
 * @Date: 2024-02-18 00:20:18 
 * @Last Modified by: Zhou Zijian
 * @Last Modified time: 2024-02-18 01:25:03
 */

#include <cstdio>
#include <omp.h>

void demo_for_1()
{
#pragma omp parallel for
    for (int i = 0; i < 10; ++i) {
        printf("ThreadId = %d\n", omp_get_thread_num());
    }
}

void demo_for_2()
{
#pragma omp for
    for (int i = 0; i < 10; ++i) {
        printf("ThreadId = %d\n", omp_get_thread_num());
    }
}

void demo_for_3()
{
#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < 10; ++i) {
            printf("ThreadId = %d\n", omp_get_thread_num());
        }
    }
}

int main()
{
    demo_for_3();
    return 0;
}