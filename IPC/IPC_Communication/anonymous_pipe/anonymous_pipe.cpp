#include <iostream>
#include <unistd.h>
#include <cstring>

int main() {
	int fd[2];
	pid_t pid;
	char buffer[128];

	// Create the pipe
	if (pipe(fd) == -1) {
		perror("pipe");
		return 1;
	}

	pid = fork();
	if (pid < 0) {
		perror("fork");
		return 1;
	} else if (pid == 0) {
		// Child process: read from pipe
		close(fd[1]); // Close write end
		int n = read(fd[0], buffer, sizeof(buffer) - 1);
		if (n > 0) {
			buffer[n] = '\0';
			std::cout << "Child received: " << buffer << std::endl;
		}
		close(fd[0]);
	} else {
		// Parent process: write to pipe
		close(fd[0]); // Close read end
		const char* msg = "Hello from parent via anonymous pipe!";
		write(fd[1], msg, strlen(msg));
		close(fd[1]);
	}
	return 0;
}
