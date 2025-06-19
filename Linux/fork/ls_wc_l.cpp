#include <unistd.h>
#include <iostream>
#include <sys/types.h>
using namespace std;

int main()
{
    // 1 create pipe
    int fd[2];
    if (pipe(fd) == -1)
    {
        /* code */
        cerr << "pipe failed " << endl;
    }

    pid_t pid = fork();
    if (-1 == pid)
    {
        /* code */
        cerr << "fork failed " << endl;
    }
    else if (pid > 0)
    {
        /* code */
        // child read
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);
        close(fd[0]);
    }
    else if (pid ==0)
    {
        /* code */
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
        close(fd[1]);
    }
    
    return 0;

}