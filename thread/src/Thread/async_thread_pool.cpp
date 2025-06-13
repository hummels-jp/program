#include <iostream>
#include <vector>
#include <future>
#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

class AsyncThreadPool {
public:
    // Constructor to initialize the thread pool with a given number of threads
    // The threads will be created and start waiting for tasks
    explicit AsyncThreadPool(size_t threadCount) : stop(false) {
        for (size_t i = 0; i < threadCount; ++i) {
            workers.emplace_back(&AsyncThreadPool::workerThread, this);
        }
    }

    ~AsyncThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }

        condition.notify_all();
        for (std::thread &worker : workers) {
            worker.join();
        }
    }

    // Enqueue a task to the thread pool
    template <typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
        using returnType = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<returnType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<returnType> result = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queueMutex);

            if (stop) {
                throw std::runtime_error("Enqueue on stopped ThreadPool");
            }

            tasks.emplace([task]() { (*task)(); });
        }

        condition.notify_one();
        return result;
    }

private:
    // Worker thread function
    void workerThread() {
        while (true) {
            std::function<void()> task;

            {
                std::unique_lock<std::mutex> lock(queueMutex);
                condition.wait(lock, [this]() { return stop || !tasks.empty(); });

                if (stop && tasks.empty()) {
                    return;
                }

                task = std::move(tasks.front());
                tasks.pop();
            }

            task();
        }
    }

    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
};

int main() {
    AsyncThreadPool pool(4);

    std::vector<std::future<int>> results;

    // Enqueue 8 tasks
    // Each task will sleep for 100 milliseconds and then return its index squared
    for (int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue([i]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                std::cout << "Task " << i << " is running on thread " << std::this_thread::get_id() << std::endl;
                return i * i;
            })
        );
    }

    for (auto &&result : results) {
        std::cout << "Result: " << result.get() << std::endl;
    }

    return 0;
}