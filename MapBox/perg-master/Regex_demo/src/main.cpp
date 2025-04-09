#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
using namespace std;

struct Test
{
    /* data */
    int a;
    int b;
};


void* callback(void* arg) {
    for (int i = 0; i < 5; ++i) {
        printf("子线程: i = %d\n", i);
    }
    printf("子线程: %ld\n", pthread_self());
    struct Test* test = (struct Test*)arg;
    test->a = 1;
    test->b = 2;
    printf("子线程: a = %d, b = %d\n", test->a, test->b);
    pthread_exit((void*)test); // 退出线程并返回

    return NULL;
}

int main() {
    pthread_t tid;
    Test test;
    test.a = 0;
    test.b = 0;
    cout << "主线程: " << test.a << ", " << test.b << std::endl;

    pthread_create(&tid, NULL, callback, &test); // 创建子线程
    for (int i = 0; i < 5; ++i) {
        printf("主线程: i = %d\n", i);
    }
    printf("主线程: %ld\n", pthread_self());


    void* ret;
    pthread_join(tid, &ret); // 等待子线程执行完毕
    Test* result = (Test*)ret; // 获取子线程返回的值
    printf("子线程返回的值: a = %d, b = %d\n", result->a, result->b);
    
    return 0;
}