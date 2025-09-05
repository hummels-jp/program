#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>

int main() {
	key_t key = ftok("/tmp", 66); // Generate unique key
	int shmid = shmget(key, 1024, 0666 | IPC_CREAT); // Get shared memory
	if (shmid < 0) {
		perror("shmget");
		return 1;
	}

	// Attach to shared memory
	char* str = (char*) shmat(shmid, nullptr, 0);
	if (str == (char*)-1) {
		perror("shmat");
		return 1;
	}

	// Read data from shared memory
	std::cout << "Receiver: Data read from shared memory: " << str << std::endl;

	// Detach from shared memory
	shmdt(str);

	// Optionally remove shared memory (if you want to clean up)
	// shmctl(shmid, IPC_RMID, nullptr);

	return 0;
}
