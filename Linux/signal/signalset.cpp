#include <csignal>
#include <cstdio>
#include <unistd.h>
#include <iostream>
using namespace std;


void print_set(sigset_t* set)
{
    for (int  i = 1; i < 32; i++)
    {
        /* code */
        if (sigismember(set, i))
        {
            /* code */
            cout << "1 ";
        }
        else
        {
            cout << "0 ";
        }
        
    }
    cout << endl;
    
}

int main() {
    sigset_t set, oldset;

    // 初始化信号集为空
    sigemptyset(&set);
    // 将 SIGINT 添加到信号集
    sigaddset(&set, SIGINT);

    // 阻塞 SIGINT 信号
    if (sigprocmask(SIG_BLOCK, &set, &oldset) != 0) {
        perror("sigprocmask");
        return 1;
    }

    printf("SIGINT is now blocked. Press Ctrl+C, nothing will happen for 5 seconds...\n");

    while (true)
    {
        /* code */
        sigset_t pending_set;
        sigpending(&pending_set);
        print_set(&pending_set);
    
    }
    


    return 0;
}