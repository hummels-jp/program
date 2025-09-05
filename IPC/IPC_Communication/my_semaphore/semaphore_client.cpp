#include <iostream>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
using namespace std;

// Union required for semctl
union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int main()
{
    // 1 get semaphore
    key_t key = ftok("/tmp", 123);
    int sem_id = semget(key, 1, 0666| IPC_CREAT);
    if(sem_id < 0)
    {
        perror("semget failed ");
        return -1;
    }

    // 2 P operation, Acquiring semaphore
    struct sembuf p_operation = {0, -1, SEM_UNDO};
    cout << "P operation, Acquiring Semaphore: " << endl;
    semop(sem_id, &p_operation, 1);
    sleep(5);

    // 3 V operation, Releasing semaphore
    struct sembuf v_operation = {0, 1, SEM_UNDO};
    cout << "V operation, Releasing Semaphore: " << endl;
    semop(sem_id, &v_operation, 1);

    return 0;
}