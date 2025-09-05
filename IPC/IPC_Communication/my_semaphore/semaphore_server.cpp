#include <iostream>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
using namespace std;

// Union required for semctl system call to set/get semaphore values
union semun {
	int val;                // Value for SETVAL
	struct semid_ds *buf;   // Buffer for IPC_STAT, IPC_SET
	unsigned short *array;  // Array for GETALL, SETALL
};


int main()
{
    // 1 get the semaphore
    key_t key = ftok("/tmp", 65);
    int semaphore_id = semget(key, 1, 0666 | IPC_CREAT);
    if(semaphore_id < 0)
    {
        perror("semget failed ");
        return -1;
    }

    // Initialize semaphore to 1 (only if the first time)
    semun arg;
    arg.val = 1;
    semctl(semaphore_id, 0, SETVAL, arg);

    // Print current semaphore value before P operation
    int sem_val = semctl(semaphore_id, 0, GETVAL);
    std::cout << "Semaphore value before P operation: " << sem_val << std::endl;

    // p operation, semaphore minus 1
    struct sembuf p_operation = {0, -1, SEM_UNDO};
    std::cout << "Server: Waiting to enter critical section..." << std::endl;
    semop(semaphore_id, &p_operation, 1);

    // Print current semaphore value after P operation
    sem_val = semctl(semaphore_id, 0, GETVAL);
    std::cout << "Semaphore value after P operation: " << sem_val << std::endl;

    std::cout << "Server: In critical section. PID: " << getpid() << std::endl;
    sleep(5); // Simulate work
    std::cout << "Server: Leaving critical section." << std::endl;

    // V operation (release semaphore)
    struct sembuf v = {0, 1, SEM_UNDO};
    semop(semaphore_id, &v, 1);

    // Print current semaphore value after V operation
    sem_val = semctl(semaphore_id, 0, GETVAL);
    std::cout << "Semaphore value after V operation: " << sem_val << std::endl;

    // Optionally remove semaphore (if you want to clean up)
    // semctl(semaphore_id, 0, IPC_RMID);

}