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

    const char* file_name = "mmap_test";
    int fd = open(file_name, O_RDWR , 0666);
    if (fd == -1)
    {
        /* code */
        cerr << "open failed " << endl;
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

    // 4 read data from mmap
    while (true)
    {
        /* code */
        sleep(1);
        student* pst = static_cast<student*>(addr);
        cout << "id: " << pst->id << " name: " << pst->name << " age: " << pst->age << endl;
    }

    // delete mmap and close file
    munmap(addr, sizeof(st1));
    close(fd);


    return 0;
}