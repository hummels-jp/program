#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>

int main() {
	key_t key = ftok("/tmp", 66); // Generate unique key
	int shmid = shmget(key, 1024, 0666 | IPC_CREAT); // Create shared memory
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

	// Write data to shared memory
	std::strcpy(str, "Hello from sender via System V shared memory!");
	std::cout << "Sender: Data written to shared memory." << std::endl;

	// Detach from shared memory
	shmdt(str);
	return 0;
}
