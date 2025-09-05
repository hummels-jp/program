#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
using namespace std;

int main()
{
    const char* fifo_path = "/tmp/myfifo";

    // open fifo, write only
    int fd = open(fifo_path, O_WRONLY);
    if(fd < 0)
    {
        perror("open");
        return -1;
    }
    // write fifo
    string msg = "hello from client via fifo";
    write(fd, msg.c_str(), msg.size());
    cout << "send message " << endl;

    close(fd);

    return 0;

}