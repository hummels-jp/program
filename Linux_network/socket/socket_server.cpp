
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create a socket (IPv4, TCP)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        // Print error if socket creation fails
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set address and port for the server
    address.sin_family = AF_INET;            // IPv4
    address.sin_addr.s_addr = INADDR_ANY;    // Listen on all interfaces
    address.sin_port = htons(8888);          // Port 8888 (host to network short)

    // Bind the socket to the specified IP and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections (max 3 in queue)
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port 8888..." << std::endl;

    // Accept a client connection
    client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (client_fd < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Read data sent by the client
    int valread = read(client_fd, buffer, 1024);
    std::cout << "Received: " << buffer << std::endl;

    // Echo the received data back to the client
    send(client_fd, buffer, valread, 0);

    // Close the client socket
    close(client_fd);
    // Close the server socket
    close(server_fd);
    return 0;
}