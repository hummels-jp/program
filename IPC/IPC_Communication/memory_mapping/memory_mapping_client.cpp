#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

int main() {
	const char* filename = "/tmp/mmap_ipc_file";
	size_t filesize = 4096;

	// 1. Open the file
	int fd = open(filename, O_RDONLY);
	if (fd < 0) {
		perror("open");
		return 1;
	}

	// 2. Map the file to memory
	void* addr = mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED) {
		perror("mmap");
		close(fd);
		return 1;
	}

	// 3. Read the message from the mapped memory
	std::cout << "Client read: " << (char*)addr << std::endl;

	// 4. Cleanup
	munmap(addr, filesize);
	close(fd);
	return 0;
}
