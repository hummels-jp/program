#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main()
{
    pid_t pid = fork();
    if (pid > 0)
    {
        /* code */
        cout << "parent pid " << getpid() << endl;

        sleep(5);
    }
    else if (pid == 0)
    {
        /* code */
        cout << "child pid" << getpid() << endl;
        cout << "send signal " << endl;
        kill(getppid(), SIGINT);
    }
    
    
    return 0;
}