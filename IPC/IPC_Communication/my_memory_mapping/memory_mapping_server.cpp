#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
using namespace std;

int main()
{
    const char* file_path ="/tmp/mmap_ipc_file";
    const char* message = "Hello from memory-mapped server!";
    size_t file_size = 4096;

    // 1 create or open the file
    int fd = open(file_path, O_CREAT | O_RDWR, 0666);
    if(fd < 0)
    {
        perror("open failed ");
        return -1;
    }

    // 2 set the filesize
    int result = ftruncate(fd, file_size);
    if(result == -1)
    {
        perror("ftruncate failed");
        close(fd);
        return -1;
    }

    // 3 Map the file to memory
    void* addr = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(addr == MAP_FAILED)
    {
        perror("mmap failed");
        close(fd);
        return -1;
    }

    // 4 write the message into the memory
    memset(addr, 0, file_size);
    strcpy((char*)addr, message);
    cout << "server write: " << message << endl;

    // 5 wait for client to read (press enter to leave)
    cout << "wait client to read, press enter to leave " << endl;
    cin.get();

    // 6 close memory mapping
    munmap(addr, file_size);
    close(fd);

    return 0;
}