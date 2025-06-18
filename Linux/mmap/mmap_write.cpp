#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
using namespace std;


struct student
{
    /* data */
    int id;
    char name[256];
    int age;

};


int main()
{
    student st1{1, "xiaoming", 18};
    student* pst;
    // 1 create or open the file
    const char* file_name = "mmap_test";
    int fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1)
    {
        /* code */
        cerr << "open failed " << endl;
        return 1;
    }

    // 2 truncate the file
    if (ftruncate(fd, sizeof(st1)) == -1)
    {
        /* code */
        cerr << "ftruncate error " << endl;
        close(fd);

        return 1;
    }

    // 3 create the mmap
    void* addr = mmap(NULL, sizeof(st1), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
    if (addr == MAP_FAILED)
    {
        /* code */
        cerr << "mmap failed " << endl;
        return 1;
    }

    // 4 write data into mmap
    while (true)
    {
        /* code */
        sleep(1);
        memcpy(static_cast<student*> (addr), &st1, sizeof(st1));
        st1.id++;
    }

    // delete mmap and close file
    munmap(addr, sizeof(st1));
    close(fd);
    return 0;
}