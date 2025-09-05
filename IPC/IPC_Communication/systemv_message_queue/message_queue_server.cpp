#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>

// Define message buffer structure
struct msg_buffer {
	long msg_type;
	char msg_text[100];
};

int main() {
	key_t key = ftok("/tmp", 65); // Generate unique key
	int msgid = msgget(key, 0666 | IPC_CREAT); // Create message queue
	if (msgid < 0) {
		perror("msgget");
		return 1;
	}

	msg_buffer message;
	std::cout << "Server: Waiting for messages..." << std::endl;
	// Receive message of type 1
	msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
	std::cout << "Received message: " << message.msg_text << std::endl;

	// Destroy the message queue
	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}
