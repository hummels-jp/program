#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void hello(void) {
    // 获取线程编号和线程总数
    // omp_get_thread_num() 获取当前线程的编号
    int my_rank = omp_get_thread_num();
    // omp_get_num_threads() 获取当前线程的总数
    // 线程编号从0开始，线程总数从1开始
    int thread_count = omp_get_num_threads();
    printf("Hello from thread %d of %d.\n", my_rank, thread_count);
}

// 编译命令 g++ -std=c++11 -o .\test_src\openmp_001 .\test_src\openmp_001.cpp -fopenmp
int main(int argc, char* argv[]) {
    // 检查命令行参数是否正确
    // int thread_count = strtol(argv[1], NULL, 10);
    int thread_count = 10;

    // 检查线程数是否大于0
    // 
    #pragma omp parallel num_threads(thread_count)
    hello();

    return 0;
}