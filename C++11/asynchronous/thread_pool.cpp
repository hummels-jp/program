#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <vector>
#include <future>
#include <memory>

// 线程安全的队列实现
template<typename T>
class SafeQueue {
private:
    std::queue<T> queue;
    mutable std::mutex mutex;
    std::condition_variable cv;
    bool stop;

public:
    SafeQueue() : stop(false) {}

    void push(T value) {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(std::move(value));
        cv.notify_one();
    }

    bool pop(T& value) {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [this] { return !queue.empty() || stop; });
        
        if (stop && queue.empty()) 
            return false;
        
        value = std::move(queue.front());
        queue.pop();
        return true;
    }

    void stop_queue() {
        std::lock_guard<std::mutex> lock(mutex);
        stop = true;
        cv.notify_all();
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }

    size_t size() {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.size();
    }
};

// 线程池实现
class ThreadPool {
private:
    std::vector<std::thread> workers;
    SafeQueue<std::function<void()>> tasks;
    std::mutex pool_mutex;
    bool stop;

public:
    // 构造函数：创建线程池
    ThreadPool(size_t num_threads = std::thread::hardware_concurrency()) : stop(false) {
        for (size_t i = 0; i < num_threads; ++i) {
            workers.emplace_back([this, i] {
                while (true) {
                    std::function<void()> task;
                    // 
                    bool got_task = tasks.pop(task);
                    
                    if (!got_task) {
                        std::cout << "Worker " << i << " shutting down\n";
                        break;
                    }
                    
                    std::cout << "Worker " << i << " executing task\n";
                    task();
                }
            });
        }
    }

    // 析构函数：等待所有线程完成
    ~ThreadPool() {
        if (!stop) {
            shutdown();
        }
    }

    // 添加任务到线程池
    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::invoke_result<F, Args...>::type> {
        using return_type = typename std::invoke_result<F, Args...>::type;
        
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        std::future<return_type> result = task->get_future();
        
        {
            std::lock_guard<std::mutex> lock(pool_mutex);
            if (stop) {
                throw std::runtime_error("Cannot enqueue on stopped ThreadPool");
            }
            
            tasks.push([task]() { (*task)(); });
        }
        
        return result;
    }

    // 关闭线程池
    void shutdown() {
        {
            std::lock_guard<std::mutex> lock(pool_mutex);
            stop = true;
        }
        
        tasks.stop_queue();
        
        for (std::thread& worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    // 获取线程数量
    size_t size() const {
        return workers.size();
    }

    // 获取待处理任务数量
    size_t task_count() const {
        return tasks.size();
    }
};

// 测试函数
int calculate(int value) {
    // 模拟耗时计算
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    return value * value;
}

int main() {
    // 创建线程池，使用4个线程
    ThreadPool pool(4);
    std::cout << "Thread pool created with " << pool.size() << " threads\n";

    // 创建一些future来保存任务结果
    std::vector<std::future<int>> results;

    // 提交10个任务
    for (int i = 1; i <= 10; ++i) {
        std::cout << "Submitting task " << i << std::endl;
        results.push_back(pool.enqueue(calculate, i));
    }

    // 获取并打印结果
    for (size_t i = 0; i < results.size(); ++i) {
        std::cout << "Task " << (i + 1) << " result: " << results[i].get() << std::endl;
    }

    // 线程池会在析构时自动关闭
    std::cout << "Main thread done, thread pool will be destroyed\n";

    return 0;
}