#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
using namespace std;

#define PORT 8080
#define BUF_SIZE 1024

int main()
{
    //1  create listen socket
    int listenfd = 0;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1)
    {
        /* code */
        cerr << "listen socket failed " << endl;
        exit(1);
    }

    // 2 bind the server address to the listen socket
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT); // conver local to network, port
    
    if (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        /* code */
        cerr << "bind error " << endl;
        exit(1);
    }

    // 3 set the listen number
    if (listen(listenfd, 5) < 0)
    {
        /* code */
        cerr << "listen error" << endl;
        exit(1);
    }

    cout << "server listening on port "  << PORT << endl;

    // 4 accept the connect from client
    struct sockaddr_in client_addr;
    socklen_t client_len;
    client_len = sizeof(client_addr);
    int connect_fd = 0;
    connect_fd = accept(listenfd, (struct sockaddr*)&serv_addr, &client_len);
    if (connect_fd < 0)
    {
        /* code */
        cerr << "accept failed " << endl;
        exit(1);
    }
    cout << "client connected " << endl;
    

    // 5 read and write data 
    char buffer[BUF_SIZE];
    while (1)
    {
        /* code */
        // read
        ssize_t n = read(connect_fd, buffer, BUF_SIZE-1);

        // convert
        if (n<=0)
        {
            /* code */
            break;
        }
        buffer[n] = '\0';
        for (int i = 0; i < n; i++)
        {
            /* code */
            buffer[i] = toupper(buffer[i]);
        }

        // write
        write(connect_fd, buffer, n);
    
    }

    close(listenfd);
    close(connect_fd);
    
    return 0;
}