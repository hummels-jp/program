#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <map>
#include <memory>

class ThreadPool {
public:
    using Ptr = std::shared_ptr<ThreadPool>;

    // 获取指定线程数的线程池单例
    static Ptr getInstance(size_t numThreads) {
        std::lock_guard<std::mutex> lock(mapMutex_);
        auto it = poolMap_.find(numThreads);
        if (it != poolMap_.end()) {
            return it->second;
        }
        Ptr pool(new ThreadPool(numThreads));
        poolMap_[numThreads] = pool;
        return pool;
    }

    // 禁止拷贝和赋值
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    template <typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        using ReturnType = decltype(f(args...));
        auto task = std::make_shared<std::packaged_task<ReturnType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        std::future<ReturnType> result = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queueMutex_);
            if (stop_) throw std::runtime_error("enqueue on stopped ThreadPool");
            tasks_.emplace([task]() { (*task)(); });
        }
        condition_.notify_one();
        return result;
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex_);
            stop_ = true;
        }
        condition_.notify_all();
        for (std::thread& worker : workers_) {
            worker.join();
        }
    }

private:
    ThreadPool(size_t numThreads) : stop_(false) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers_.emplace_back([this]() {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queueMutex_);
                        condition_.wait(lock, [this]() { return stop_ || !tasks_.empty(); });
                        if (stop_ && tasks_.empty()) return;
                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }
                    task();
                }
            });
        }
    }

    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex queueMutex_;
    std::condition_variable condition_;
    bool stop_;

    static std::map<size_t, Ptr> poolMap_;
    static std::mutex mapMutex_;
};

// 静态成员初始化
std::map<size_t, ThreadPool::Ptr> ThreadPool::poolMap_;
std::mutex ThreadPool::mapMutex_;

// 示例
int main() {
    auto pool4 = ThreadPool::getInstance(4);
    auto pool8 = ThreadPool::getInstance(8);

    auto f1 = pool4->enqueue([] { std::cout << "Hello from pool4\n"; });
    auto f2 = pool8->enqueue([] { std::cout << "Hello from pool8\n"; });

    f1.get();
    f2.get();

    return 0;
}