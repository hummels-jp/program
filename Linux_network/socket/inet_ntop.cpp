#include <iostream>
#include <arpa/inet.h>
#include <cstring>



int main() {
    // htons()  // convert local byte order to network byte order, short for port
    // htonl()  convert local byte order to network byte order, long for ip address
    // ntohs()  convert     
    struct in_addr addr;
    addr.s_addr = inet_addr("192.168.1.10");

    char dst[INET_ADDRSTRLEN];
    const char* result = inet_ntop(AF_INET, &addr, dst, INET_ADDRSTRLEN);

    if (result) {
        std::cout << "IPv4 address: " << dst << std::endl;
    } else {
        std::cerr << "inet_ntop failed" << std::endl;
    }

    return 0;
}