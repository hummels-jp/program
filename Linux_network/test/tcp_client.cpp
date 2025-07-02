#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;

#define PORT 8080
#define BUF_SIZE 1024


int main()
{
    // 1 create socket
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        /* code */
        cerr << "socket failed " << endl;
        exit(1); 
    }

    // 2 connet to the server
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT); // convert local byte order to network byte order, port

    if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        /* code */
        cerr << "connect failed " << endl;
        exit(1);
    }
    cout << "server connected successed " << endl;

    // 3 write and read
    char buffer[BUF_SIZE];

    while (fgets(buffer, BUF_SIZE, stdin) != NULL)
    {
        /* code */
        // write
        write(socket_fd, buffer, strlen(buffer));

        // read
        ssize_t n = read(socket_fd, buffer, BUF_SIZE - 1);
        if (n <= 0)
        {
            /* code */
            break;
        }
        buffer[n] = '\0';
        
        cout << "from server: " << buffer << endl;
    }
    
    
    close(socket_fd);
    
    return 0;
}