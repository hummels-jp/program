#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>

int main() {
	const char* fifo_path = "/tmp/myfifo";
	// 打开 FIFO 以写入
	int fd = open(fifo_path, O_WRONLY);
	if (fd < 0) {
		perror("open");
		return 1;
	}

	const char* msg = "Hello from client via FIFO!";
	write(fd, msg, strlen(msg));
	std::cout << "Sent to server: " << msg << std::endl;

	close(fd);
	return 0;
}
