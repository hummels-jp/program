#include <iostream>
#include <mqueue.h>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
	const char* queue_name = "/my_posix_mq";
	mqd_t mq = mq_open(queue_name, O_RDONLY | O_CREAT, 0666, nullptr);
	if (mq == (mqd_t)-1) {
		perror("mq_open");
		return 1;
	}

	char buffer[128];
	ssize_t bytes_read = mq_receive(mq, buffer, sizeof(buffer), nullptr);
	if (bytes_read >= 0) {
		buffer[bytes_read] = '\0';
		std::cout << "Receiver: Message received: " << buffer << std::endl;
	} else {
		perror("mq_receive");
	}

	mq_close(mq);
	// Optionally remove the message queue
	// mq_unlink(queue_name);
	return 0;
}
