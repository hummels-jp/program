#include <iostream>
#include <functional>
#include <queue>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <future>
#include <utility>

class ThreadPool {
public:
    ThreadPool(size_t numThreads) {
        for (size_t i = 0; i < numThreads; ++i) 
        {
            workers.emplace_back([this]() {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        // 等待条件变量，直到有任务可用或线程池停止
                        condition.wait(lock, [this]() { return stop || !tasks.empty(); });
                        // 如果线程池停止且任务队列为空，则退出线程
                        if (stop && tasks.empty()) return;
                        // 如果任务队列不为空，则获取一个任务
                        task = std::move(tasks.front());
                        // 从队列中移除任务
                        tasks.pop();
                    }
                    // 执行任务
                    task(); // 执行任务
                }
            });
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        // 通知所有线程停止工作
        condition.notify_all();
        // 等待所有线程完成工作
        for (std::thread &worker : workers) {
            worker.join();
        }
    }

    // 添加任务到队列，并返回一个 future
    template <typename Func, typename... Args>
    auto addTask(Func&& func, Args&&... args) -> std::future<decltype(func(args...))> 
    {   
        // 使用 std::packaged_task 来包装任务 并返回一个 std::future
        // std::packaged_task 可以将函数和参数绑定在一起，并提供一个 std::future 来获取结果
        // dec
        using ReturnType = decltype(func(args...));
        auto task = std::make_shared<std::packaged_task<ReturnType()>>(
            std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
        );

        std::future<ReturnType> future = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();
        return future;
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop = false;
};

int main() {
    ThreadPool pool(4); // 创建一个包含 4 个线程的线程池

    // 添加任务并获取 future
    auto future1 = pool.addTask([]() -> int {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 42; 
    });

    auto future2 = pool.addTask([]() -> double {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return 3.14; 
    });

    auto future3 = pool.addTask([](const std::string& name) -> std::string {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return "Hello, " + name + "!";
    }, "ThreadPool");

    // 获取任务的返回值
    std::cout << "Result 1: " << future1.get() << std::endl; // 等待并获得第一个任务的结果
    std::cout << "Result 2: " << future2.get() << std::endl; // 等待并获得第二个任务的结果
    std::cout << "Result 3: " << future3.get() << std::endl; // 等待并获得第三个任务的结果

    return 0;
}