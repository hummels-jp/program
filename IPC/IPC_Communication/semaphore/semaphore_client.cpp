#include <iostream>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

// Union required for semctl
union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int main() {
	key_t key = ftok("/tmp", 75);
	int semid = semget(key, 1, 0666 | IPC_CREAT);
	if (semid < 0) {
		perror("semget");
		return 1;
	}

    // P operation
    struct sembuf p_operation = {0, -1, SEM_UNDO};
    std::cout << "Client: Acquiring semaphore (P operation)..." << std::endl;
    semop(semid, &p_operation, 1);
    sleep(5);

	struct sembuf v_operation = {0, 1, SEM_UNDO}; // V operation (signal)
	std::cout << "Client: Releasing semaphore (V operation)..." << std::endl;
	semop(semid, &v_operation, 1); // Signal (V)
	std::cout << "Client: Semaphore released." << std::endl;

	// Optionally remove semaphore (if you want to clean up)
	// semctl(semid, 0, IPC_RMID);

	return 0;
}
