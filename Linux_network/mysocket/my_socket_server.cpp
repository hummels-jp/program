
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>

int main()
{

    // 1 create a socket
    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == 0)
    {
        perror("socket failed \n");
        exit(EXIT_FAILURE);
    }

    // 2 set address and port for the server
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8888);

    // 3 bind the socket to the server ip and port
    int result = bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    if(result < 0)
    {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4 set the listening count for the incoming connection (maxmum 3)
    if(listen(server_fd, 3) < 0)
    {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    std::cout << "server listening on port 8888 " << std::endl; 

    // 5 Accept a client connection
    socklen_t addrlen = sizeof(address);
    int client_fd = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    if(client_fd < 0)
    {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 6 Read data sent by client
    char buffer[1024] = {0};
    int nRead = read(client_fd, buffer, 1024);
    if (nRead > 0) {
        std::cout << "received: " << buffer << std::endl;
        // Convert all characters in buffer to uppercase
        for (int i = 0; i < nRead; ++i) {
            buffer[i] = toupper(static_cast<unsigned char>(buffer[i]));
        }
        // 7 send data to the client
        send(client_fd, buffer, nRead, 0);
    } else {
        std::cerr << "read failed or no data received" << std::endl;
    }

    // 8 close the client socket and server socket
    close(client_fd);
    close(server_fd);

    return 0;
}