#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
using namespace std;

int main()
{
    // 1 create file mmap
    const char* file_name = "mmap_test.txt";
    const size_t size = 4096;

    // int fd = open(file_name, O_RDWR | O_CREAT, 0666);
    // if (fd == -1)
    // {
    //     /* code */
    //     cerr << "open file failed " << endl;
    //     return 1;
    // }

    // 2 create file size is 0, need to expand
    // if (ftruncate(fd, size) == -1)
    // {
    //     cerr << "ftruncate failed " << endl;
    //     close(fd);
    //     return 1;
    //     /* code */
    // }

    // 3 create mmap
    // void* addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // anonymous mmap
    void* addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    if (addr == MAP_FAILED)
    {
        /* code */
        cerr << "mmap failed " << endl;

        return 1;
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        /* code */
        // 4 write data into mmap
        const char* msg = "hello, mmap";
        cout << "child write mmap " << endl;
        strcpy(static_cast<char*>(addr), msg);
    }
    else if (pid > 0)
    {
        wait(NULL);   
        /* code */
        // 5 read data from mmap
        cout << "parent read mmap " << endl;
        cout << "read from mmap: " << static_cast<char*> (addr) << endl;
    }
    else if (pid == -1)
    {
        cerr << "fork failed " << endl;
        return 1;
    }
    
    // 6 delete mmap and close file
    munmap(addr, size);

    return 0;
}