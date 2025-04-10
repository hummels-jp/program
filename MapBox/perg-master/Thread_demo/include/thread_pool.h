#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>

class ThreadPool {
public:
    ThreadPool(size_t numThreads); // 声明 
    ~ThreadPool();                 // 声明

    template <class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::invoke_result<F, Args...>::type>;

private:
    std::vector<std::thread> workers; // 线程池
    std::queue<std::function<void()>> tasks; // 任务队列

    std::mutex queueMutex; // 互斥锁
    std::condition_variable condition; // 条件变量
    std::atomic<bool> stop; // 停止标志
};

// 模板函数必须定义在头文件中
// 因为编译器需要在实例化时看到函数的定义
// add task to the queue
template <class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) -> std::future<typename std::invoke_result<F, Args...>::type>
{
    // create a packaged task
    using returnType = typename std::invoke_result<F, Args...>::type;

    // wrap the function and its arguments in a packaged task
    auto task = std::make_shared<std::packaged_task<returnType()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    // get the future from the packaged task
    std::future<returnType> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        if (stop) throw std::runtime_error("enqueue on stopped ThreadPool");
        tasks.emplace([task]() { (*task)(); });
    }

    // notify one thread that a new task is available
    // 这里使用notify_one()而不是notify_all()，因为我们只需要唤醒一个线程
    condition.notify_one();

    // 返回future对象
    return res;
}

#endif // THREAD_POOL_H
