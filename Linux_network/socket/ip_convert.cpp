#include <arpa/inet.h>
#include <cstring>
#include <iostream>

int main() {
    const char* ip_str = "192.168.1.1";
    struct in_addr ipv4_addr; // after convert, 

    // IPv4
    if (inet_pton(AF_INET, ip_str, &ipv4_addr) == 1) {
        std::cout << "IPv4 numeric: " << ipv4_addr.s_addr << std::endl;
    } else {
        std::cerr << "Invalid IPv4 address" << std::endl;
    }

    // IPv6
    const char* ip6_str = "2001:db8::1";
    struct in6_addr ipv6_addr;
    if (inet_pton(AF_INET6, ip6_str, &ipv6_addr) == 1) {
        std::cout << "IPv6 address parsed successfully" << std::endl;
    } else {
        std::cerr << "Invalid IPv6 address" << std::endl;
    }
    return 0;
}