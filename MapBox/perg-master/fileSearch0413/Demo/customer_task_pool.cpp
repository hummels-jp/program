#include <iostream>
#include <vector>
#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

class ThreadPool {
public:
    explicit ThreadPool(size_t numThreads) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back(&ThreadPool::worker, this); // Bind worker function
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& worker : workers) {
            worker.join();
        }
    }

    template <typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::invoke_result<F, Args...>::type> {
        using returnType = typename std::invoke_result<F, Args...>::type;

        auto promise = std::make_shared<std::promise<returnType>>();
        std::future<returnType> result = promise->get_future();

        {
            std::unique_lock<std::mutex> lock(queueMutex);
            if (stop) throw std::runtime_error("ThreadPool is stopped");

            tasks.emplace([promise, f = std::forward<F>(f), ...args = std::forward<Args>(args)]() mutable {
                try {
                    if constexpr (std::is_void_v<returnType>) {
                        std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
                        promise->set_value();
                    } else {
                        promise->set_value(std::invoke(std::forward<F>(f), std::forward<Args>(args)...));
                    }
                } catch (...) {
                    promise->set_exception(std::current_exception());
                }
            });
        }
        condition.notify_one();
        return result;
    }

private:
    void worker() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                condition.wait(lock, [this]() { return stop || !tasks.empty(); });
                if (stop && tasks.empty()) return;
                task = std::move(tasks.front());
                tasks.pop();
            }
            task(); // Execute the task
        }
    }

    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop = false;
};

// A class with a member function
class MyClass {
public:
    int memberFunction(int x, int y) {
        std::cout << "Processing " << x << " + " << y << " in thread " << std::this_thread::get_id() << std::endl;
        return x + y;
    }
};

int main() {
    ThreadPool pool(4); // Create a thread pool with 4 threads
    MyClass obj;

    // Enqueue tasks that call the member function
    std::vector<std::future<int>> results;
    for (int i = 0; i < 10; ++i) {
        results.emplace_back(pool.enqueue(&MyClass::memberFunction, &obj, i, i + 1));
    }

    // Get and print the results
    for (auto& result : results) {
        std::cout << "Result: " << result.get() << std::endl;
    }

    return 0;
}