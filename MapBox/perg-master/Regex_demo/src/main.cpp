#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#include <process.h>
#ifdef _WIN32
unsigned __stdcall callback(void* arg) {
#else
void callback(void* arg) {
#endif
#ifndef _WIN32
#include <pthread.h>
#endif
#endif


#include <stdio.h>
    #ifdef _WIN32
        HANDLE thread = (HANDLE)_beginthreadex(NULL, 0, callback, NULL, 0, NULL);
        CloseHandle(thread);
    #else
        pthread_t tid;
        pthread_create(&tid, NULL, callback, NULL);
    #endif
    for (int i = 0; i < 5; ++i) {
        printf("子线程: i = %d\n", i);
        printf("子线程: %ld\n", pthread_self());
    }
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, callback, NULL);
    for (int i = 0; i < 5; ++i) {
        printf("主线程: i = %d\n", i);
        printf("主线程: %ld\n", pthread_self());
    }
    return 0;
}