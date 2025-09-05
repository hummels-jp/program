#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
using namespace std;

int main()
{
    // 1 create named pipe file
    const char* pipe_file = "/tmp/myfifo";
    mkfifo(pipe_file, 0666);

    // server process read from pipe
    char buffer[1024] = {0};
    std::cout << "waiting client to send data ... " << std::endl;

    // open the pipe file, read only
    int fd = open(pipe_file, O_RDONLY);
    if(fd < 0)
    {
        perror("open");
        return -1;
    }

    // read data from the fifo file
    int n = read(fd, buffer, sizeof(buffer) - 1);
    if(n > 0)
    {
        buffer[n] = '\0';
        cout << "received from client: " << buffer << endl;
    }
    else
    {
        cout << "No data received " << endl; 
        return -1;
    }

    return 0;
}