#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* callback(void* arg) {
    for (int i = 0; i < 5; ++i) {
        printf("子线程: i = %d\n", i);
    }
    printf("子线程: %ld\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, callback, NULL);
    for (int i = 0; i < 5; ++i) {
        printf("主线程: i = %d\n", i);
    }
    printf("主线程: %ld\n", pthread_self());
    // sleep(1); // 等待子线程执行完毕
    pthread_exit(NULL); // 等待子线程执行完毕
    return 0;
}