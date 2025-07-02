#include <iostream>
#include <arpa/inet.h> // Linux/Unix 下

int main() {
    uint32_t hostlong = 0x12345678; // 主机字节序, local byte order, small endian
    uint32_t netlong = htonl(hostlong); // 转换为网络字节序 network byte order, big endian

    std::cout << "主机字节序: 0x" << std::hex << hostlong << std::endl;
    std::cout << "网络字节序: 0x" << std::hex << netlong << std::endl;

    // 典型用法：设置 sockaddr_in 结构体的 IP 地址
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = htonl(0xC0A80101); // 192.168.1.1

    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr.sin_addr), str, INET_ADDRSTRLEN);
    std::cout << "IP 地址（字符串）: " << str << std::endl; // 192.168.1.1

    return 0;
}