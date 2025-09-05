#include <iostream>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

// Union required for semctl system call to set/get semaphore values
union semun {
	int val;                // Value for SETVAL
	struct semid_ds *buf;   // Buffer for IPC_STAT, IPC_SET
	unsigned short *array;  // Array for GETALL, SETALL
};


int main() {
	key_t key = ftok("/tmp", 75);
	int semid = semget(key, 1, 0666 | IPC_CREAT);
	if (semid < 0) {
		perror("semget");
		return 1;
	}

	// Initialize semaphore to 1 (only if first time)
	semun arg;
	arg.val = 1;
	semctl(semid, 0, SETVAL, arg);

	struct sembuf p = {0, -1, SEM_UNDO}; // P operation (wait)

	std::cout << "Server: Acquiring Semaphore..." << std::endl;
	semop(semid, &p, 1); // Wait (P)
	std::cout << "Server: In critical section. PID: " << getpid() << std::endl;
	sleep(5); // Simulate work
	std::cout << "Server: Leaving critical section." << std::endl;

	// V operation (release semaphore)
	struct sembuf v = {0, 1, SEM_UNDO};
    std::cout << "Server: Releasing Semaphore..." << std::endl;
	semop(semid, &v, 1);

	// Optionally remove semaphore (if you want to clean up)
	// semctl(semid, 0, IPC_RMID);

	return 0;
}
