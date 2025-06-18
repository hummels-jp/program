#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
using namespace std;

int main() {
    // create pipe
    int fd[2];
    if (pipe(fd) == -1)
    {
        /* code */
        cerr << "pipe failed " << endl;
        return 1;
    }

    // create child process for read, parent process for write
    pid_t pid = fork();
    if (-1 == pid)
    {
        /* code */
        cerr << "fork failed " << endl;
        return 1;
    }
    else if (pid == 0)
    {
        sleep(1);
        /* code */
        // chilf pid for read
        close(fd[1]);
        char buffer[1024];
        ssize_t read_count = read(fd[0], buffer, 1023);
        if (read_count >=0)
        {
            /* code */
            buffer[read_count] = '\0';
            cout << "child received: "  << buffer << endl;
        }
        close(fd[0]);
    }
    else if (pid > 0)
    {
        
        /* code */
        // parent pid for write
        close(fd[0]);
        sleep(2);
        const char* msg = "hello, pipe";
        cout << "parent send " << msg << endl;
        write(fd[1], msg, strlen(msg));

        close(fd[1]);
        
    }

    return 0;
}