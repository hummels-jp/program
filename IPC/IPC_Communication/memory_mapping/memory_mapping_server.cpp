#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

int main() {
    const char* filename = "/tmp/mmap_ipc_file";
    const char* message = "Hello from memory-mapped server!";
    size_t filesize = 4096;

    // 1. Create or open the file
    int fd = open(filename, O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // 2. Set the file size
    if (ftruncate(fd, filesize) == -1) {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    // 3. Map the file to memory
    void* addr = mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    // 4. Write a message to the mapped memory
    std::memset(addr, 0, filesize);
    std::strcpy((char*)addr, message);
    std::cout << "Server wrote: " << message << std::endl;

    // 5. Wait for client to read (press Enter to exit)
    std::cout << "Press Enter to exit and cleanup..." << std::endl;
    std::cin.get();

    // 6. Cleanup
    munmap(addr, filesize);
    close(fd);
    // Optionally: unlink(filename);

    return 0;
}