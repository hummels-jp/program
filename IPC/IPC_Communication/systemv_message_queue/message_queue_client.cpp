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
	int msgid = msgget(key, 0666 | IPC_CREAT); // Get message queue
	if (msgid < 0) {
		perror("msgget");
		return 1;
	}

	msg_buffer message;
	message.msg_type = 1;
	std::strcpy(message.msg_text, "Hello from client!");

	// Send message to queue
	if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
		perror("msgsnd");
		return 1;
	}
	std::cout << "Client: Message sent." << std::endl;
	return 0;
}
