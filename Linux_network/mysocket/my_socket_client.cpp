
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

int main()
{
    // 1 create the socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // set server address and port
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888);

    // convert ip address from text to binary format (use localhost for testing)
    int result = inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
    if(result <= 0)
    {
        perror("ip address is not valid");
        close(sock);
        return -1;
    }

    // 2 connect to server
    result = connect(sock, (struct sockaddr*)&server_address, sizeof(server_address));
    if(result < 0)
    {
        perror("connect failed");
        close(sock);
        return -1;
    }

    // 3 send and read data
    std::string msg = "hello from client";
    send(sock, msg.c_str(), msg.size(), 0);
    std::cout << "Message sent" << std::endl;

    // 4 read from server
    char buffer[1024] = {0};
    int nRead = read(sock, buffer, 1024);
    if (nRead > 0) {
        std::cout << "read from server: " << buffer << std::endl;
    } else {
        std::cerr << "read failed or no data received" << std::endl;
    }

    // 5 close the client socket
    close(sock);
    return 0;
}