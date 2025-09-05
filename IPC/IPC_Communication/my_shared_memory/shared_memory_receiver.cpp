#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
using namespace std;

int main()
{
    // 1 create or get shared memory
    key_t key = ftok("/tmp", 65);
    int shm_id = shmget(key, 1024, 0666 | IPC_CREAT);
    if(shm_id < 0)
    {
        perror("shmget failed ");
        return -1;
    }

    // 2 Attach to shared memory
    char* str = (char*)shmat(shm_id, nullptr, 0);
    if(str == (char*)-1)
    {
        perror("shmat failed");
        return -1;
    }

    // 3 read data from shared memory
    cout << "Receiver: read data " << str << endl;

    // 4 Detach from the shared memory
    shmdt(str);

    return 0;
}