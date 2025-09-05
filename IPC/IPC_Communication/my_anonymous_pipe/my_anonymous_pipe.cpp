#include <iostream>
#include <unistd.h>
#include <cstring>

int main()
{
    // 1 create the anonymous pipe
    int fd[2]; // anonymous pipe include read and write
    if(pipe(fd) == -1)
    {
        perror("pipe failed");
        return -1;
    }

    // 2 parent process write pipe, child process read pipe
    char buffer[1024] = {0};

    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork failed ");
        return -1;
    }
    else if(pid == 0)
    {
        // child process: read from pipe
        close(fd[1]); // close write end
        int n = read(fd[0], buffer, sizeof(buffer)-1);
        if(n > 0)
        {
            buffer[n] = '\0';
            std::cout << "child received: " << buffer << std::endl;
        }
        close(fd[0]);

    }
    else
    {
        // parent process: write into pipe
        close(fd[0]);
        const char* msg = "hello from parent process";
        write(fd[1], msg, strlen(msg));
        close(fd[1]);
    }
    
    return 0;
}