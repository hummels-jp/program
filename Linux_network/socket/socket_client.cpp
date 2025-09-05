
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Create a socket (IPv4, TCP)
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        // Print error if socket creation fails
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    // Set server address and port
    serv_addr.sin_family = AF_INET;           // IPv4
    serv_addr.sin_port = htons(8888);         // Port 8888 (host to network short)

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        return -1;
    }

    // Message to send to the server
    std::string msg = "Hello from client";
    send(sock, msg.c_str(), msg.size(), 0);
    std::cout << "Message sent" << std::endl;

    // Read the response from the server
    int valread = read(sock, buffer, 1024);
    std::cout << "Received from server: " << buffer << std::endl;

    // Close the socket
    close(sock);
    return 0;
}