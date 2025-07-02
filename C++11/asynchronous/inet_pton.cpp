#include <iostream>
#include <string>
#include <cstring>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h> // 包含inet_pton
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <arpa/inet.h>  // Linux/Unix 下包含inet_pton
    #include <netinet/in.h>
    #include <sys/socket.h>
#endif

void printIPBytes(const void* addr, int family) {
    if (family == AF_INET) {
        const unsigned char* bytes = reinterpret_cast<const unsigned char*>(addr);
        std::cout << "字节表示: ";
        for (int i = 0; i < 4; i++) {
            std::cout << static_cast<int>(bytes[i]);
            if (i < 3) std::cout << ".";
        }
        std::cout << std::endl;
    } else if (family == AF_INET6) {
        const unsigned char* bytes = reinterpret_cast<const unsigned char*>(addr);
        std::cout << "字节表示: ";
        for (int i = 0; i < 16; i++) {
            std::cout << std::hex << static_cast<int>(bytes[i]);
            if (i % 2 == 1 && i < 15) std::cout << ":";
        }
        std::cout << std::dec << std::endl;
    }
}

int main() {
    #ifdef _WIN32
    // 在Windows下初始化Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup 失败" << std::endl;
        return 1;
    }
    #endif

    // IPv4 示例
    struct sockaddr_in ipv4Addr;
    memset(&ipv4Addr, 0, sizeof(ipv4Addr));
    const char* ipv4Str = "192.168.1.1";
    
    std::cout << "=== IPv4 示例 ===" << std::endl;
    std::cout << "原始IP地址: " << ipv4Str << std::endl;
    
    int result = inet_pton(AF_INET, ipv4Str, &(ipv4Addr.sin_addr));
    if (result == 1) {
        std::cout << "转换成功!" << std::endl;
        printIPBytes(&(ipv4Addr.sin_addr), AF_INET);
        
        // 将二进制地址转回文本形式
        char ipv4StrBack[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ipv4Addr.sin_addr), ipv4StrBack, INET_ADDRSTRLEN);
        std::cout << "转回文本: " << ipv4StrBack << std::endl;
    } else if (result == 0) {
        std::cerr << "输入不是有效的IPv4地址" << std::endl;
    } else {
        std::cerr << "inet_pton 错误: " << strerror(errno) << std::endl;
    }
    
    // IPv6 示例
    struct sockaddr_in6 ipv6Addr;
    memset(&ipv6Addr, 0, sizeof(ipv6Addr));
    const char* ipv6Str = "2001:0db8:85a3:0000:0000:8a2e:0370:7334";
    
    std::cout << "\n=== IPv6 示例 ===" << std::endl;
    std::cout << "原始IP地址: " << ipv6Str << std::endl;
    
    result = inet_pton(AF_INET6, ipv6Str, &(ipv6Addr.sin6_addr));
    if (result == 1) {
        std::cout << "转换成功!" << std::endl;
        printIPBytes(&(ipv6Addr.sin6_addr), AF_INET6);
        
        // 将二进制地址转回文本形式
        char ipv6StrBack[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &(ipv6Addr.sin6_addr), ipv6StrBack, INET6_ADDRSTRLEN);
        std::cout << "转回文本: " << ipv6StrBack << std::endl;
    } else if (result == 0) {
        std::cerr << "输入不是有效的IPv6地址" << std::endl;
    } else {
        std::cerr << "inet_pton 错误: " << strerror(errno) << std::endl;
    }

    // 无效IP地址示例
    std::cout << "\n=== 无效IP地址示例 ===" << std::endl;
    const char* invalidIP = "192.168.1.300";
    std::cout << "尝试转换无效IP: " << invalidIP << std::endl;
    
    result = inet_pton(AF_INET, invalidIP, &(ipv4Addr.sin_addr));
    if (result == 0) {
        std::cout << "正确检测到无效IP地址" << std::endl;
    }

    #ifdef _WIN32
    WSACleanup();
    #endif

    return 0;
}