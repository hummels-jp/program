#include <iostream>
#include <mqueue.h>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
	// Define the name of the POSIX message queue
	const char* queue_name = "/my_posix_mq";

	// Open the message queue for writing (create if it does not exist)
	mqd_t mq = mq_open(queue_name, O_WRONLY | O_CREAT, 0666, nullptr);
	if (mq == (mqd_t)-1) {
		perror("mq_open");
		return 1;
	}

	// Message to send
	const char* msg = "Hello from POSIX sender!";

	// Send the message to the queue
	if (mq_send(mq, msg, strlen(msg) + 1, 0) == -1) {
		perror("mq_send");
		mq_close(mq);
		return 1;
	}
	std::cout << "Sender: Message sent." << std::endl;

	// Close the message queue
	mq_close(mq);
	return 0;
}
