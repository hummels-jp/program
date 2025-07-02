#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <chrono>
#include <functional>
#include <atomic>

// 通用型通道，实现CSP中的通信
template<typename T>
class Channel {
private:
    std::queue<T> buffer;
    std::mutex mtx;
    std::condition_variable cv_not_empty;
    std::condition_variable cv_not_full;
    size_t capacity;
    std::atomic<bool> closed;

public:
    // 创建指定容量的通道
    explicit Channel(size_t buffer_size = 0) : capacity(buffer_size), closed(false) {}

    // 发送数据到通道
    bool send(T value) {
        std::unique_lock<std::mutex> lock(mtx);
        
        if (closed) {
            return false; // 不能向已关闭的通道发送数据
        }
        
        // 如果是有缓冲通道且已满，则等待
        if (capacity > 0 && buffer.size() >= capacity) 
        {
            cv_not_full.wait(lock, [this] { 
                return buffer.size() < capacity || closed; 
            });
            
            if (closed) {
                return false;
            }
        }
        
        buffer.push(std::move(value));
        cv_not_empty.notify_one(); // 通知等待的接收者
        return true;
    }

    // 从通道接收数据
    bool receive(T& out_value) {
        std::unique_lock<std::mutex> lock(mtx);
        
        // 等待直到通道非空或关闭
        cv_not_empty.wait(lock, [this] { 
            return !buffer.empty() || closed; 
        });
        
        // 检查是否为空且已关闭
        if (buffer.empty() && closed) {
            return false;
        }
        
        out_value = std::move(buffer.front());
        buffer.pop();
        
        cv_not_full.notify_one(); // 通知等待的发送者
        return true;
    }

    // 关闭通道，不再接受新的发送
    void close() {
        std::lock_guard<std::mutex> lock(mtx);
        closed = true;
        cv_not_empty.notify_all(); // 通知所有等待的接收者
        cv_not_full.notify_all();  // 通知所有等待的发送者
    }

    // 检查通道是否已关闭
    bool is_closed() const {
        return closed.load();
    }

    // 检查通道是否为空
    bool empty() {
        std::lock_guard<std::mutex> lock(mtx);
        return buffer.empty();
    }
};

// 数据生成进程
void producer(Channel<int>& channel, int start, int count) {
    for (int i = start; i < start + count; ++i) {
        if (!channel.send(i)) {
            std::cout << "Producer: channel closed, stopping at " << i << std::endl;
            break;
        }
        std::cout << "Producer: sent " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "Producer: finished sending data" << std::endl;
}

// 数据处理进程
void processor(Channel<int>& input, Channel<std::string>& output) {
    int value;
    while (input.receive(value)) {
        // 处理数据
        std::string result = "Processed " + std::to_string(value * value);
        std::cout << "Processor: received " << value << ", sending " << result << std::endl;
        
        if (!output.send(result)) {
            std::cout << "Processor: output channel closed" << std::endl;
            break;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
    
    // 当输入通道关闭后，关闭输出通道
    output.close();
    std::cout << "Processor: finished processing data" << std::endl;
}

// 数据消费进程
void consumer(Channel<std::string>& channel) {
    std::string value;
    while (channel.receive(value)) {
        std::cout << "Consumer: received " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    std::cout << "Consumer: finished receiving data" << std::endl;
}

int main() {
    // 创建带有缓冲区的通道
    Channel<int> numbers(5);      // 整数通道，缓冲区大小为5
    Channel<std::string> results(5); // 字符串通道，缓冲区大小为5
    
    // 启动CSP进程
    std::thread producer_thread(producer, std::ref(numbers), 1, 10);
    std::thread processor_thread(processor, std::ref(numbers), std::ref(results));
    std::thread consumer_thread(consumer, std::ref(results));
    
    // 等待生产者完成
    producer_thread.join();
    
    // 关闭第一个通道，表示数据已全部发送
    std::cout << "Main: closing numbers channel" << std::endl;
    numbers.close();
    
    // 等待处理器和消费者完成
    processor_thread.join();
    

    consumer_thread.join();
    
    std::cout << "Main: all processes completed" << std::endl;
    
    return 0;
}