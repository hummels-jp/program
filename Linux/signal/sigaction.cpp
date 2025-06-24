#include <signal.h>
#include <iostream>
#include <unistd.h>

using namespace std;

void handler(int signo)
{
    cout << "catch signo " << signo << endl;
}

int main()
{
    struct sigaction new_sa;
    struct sigaction old_sa;

    new_sa.sa_handler = handler; // 设置处理函数
    sigemptyset(&new_sa.sa_mask); // set sa_mask, only function when callback function is running
    new_sa.sa_flags = 0; // 

    sigaction(SIGINT, &new_sa, &old_sa); // register the sig callback function

    cout << "Press Ctrl+C to test signal handler..." << endl;
    pause(); // 等待信号

    return 0;
}