#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>

int main() {
    const char* fifo_path = "/tmp/myfifo";
    // Create the FIFO (named pipe) if it does not exist
    mkfifo(fifo_path, 0666);

    char buffer[128];

    std::cout << "Waiting for client to send data..." << std::endl;
    // Open FIFO for reading
    int fd = open(fifo_path, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // Read data from the FIFO
    int n = read(fd, buffer, sizeof(buffer) - 1);
    if (n > 0) {
        buffer[n] = '\0';
        std::cout << "Received from client: " << buffer << std::endl;
    } else {
        std::cerr << "No data received or read error." << std::endl;
    }

    close(fd);
    // Optionally, remove the FIFO file
    // unlink(fifo_path);

    return 0;
}