#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>

class SharedResource {
private:
    int data;
    std::shared_mutex rwLock;

public:
    SharedResource() : data(0) {}

    void writeData(int value) {
        std::unique_lock<std::shared_mutex> lock(rwLock);
        data = value;
        std::cout << "Data written: " << data << " by thread " << std::this_thread::get_id() << std::endl;
    }

    void readData() {
        std::shared_lock<std::shared_mutex> lock(rwLock);
        std::cout << "Data read: " << data << " by thread " << std::this_thread::get_id() << std::endl;
    }
};

void writer(SharedResource& resource, int value) {
    resource.writeData(value);
}

void reader(SharedResource& resource) {
    resource.readData();
}

int main() {
    SharedResource resource;

    std::vector<std::thread> threads;

    // Create writer threads
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(writer, std::ref(resource), i + 1);
    }

    // Create reader threads
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(reader, std::ref(resource));
    }

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}