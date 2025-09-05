#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
using namespace std;

int main()
{
    const char* filename = "/tmp/mmap_ipc_file";
	size_t filesize = 4096;

    // 1 open the file , read
    int fd = open(filename, O_RDONLY, 0666);
    if(fd < 0)
    {
        perror("open failed ");
        return -1;
    }

    // 2 map the file to the memory 
    void* addr = mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);
    if(addr == NULL)
    {
        perror("mmap failed");
        close(fd);
        return -1;
    }

    // 3 read from memory mapping
    cout << "read from memory mapping: " << (char*) addr << endl;

    // 4 close memory mapping
    munmap(addr, filesize);
    close(fd);

    return 0;
}