#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
using namespace std;

int main()
{
    // 1 create the shared memory
    key_t key = ftok("/tmp", 65);
    int shm_id = shmget(key, 1024, 0666|IPC_CREAT);
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

    // 3 write data to shared memory
    strcpy(str, "Hello from sender via shared memory");
    cout << "Sender: write data into shared memory" << endl;

    // 4 Detach from shared memory
    shmdt(str);
    
    return 0;
}