#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>
#include <map>
#include <chrono>

// ThreadPool class with dynamic thread management by a manager thread.
// The pool starts with min_threads (default 2) and can grow up to max_threads (default: hardware concurrency).
class ThreadPool {
public:
    explicit ThreadPool(size_t min_threads = 2, size_t max_threads = std::thread::hardware_concurrency());
    ~ThreadPool();

    // Submit a task to the thread pool, returns a future.
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;

    void shutdown();

private:
    // Worker thread function: fetches and executes tasks from the queue.
    void worker_thread();
    // Manager thread function: dynamically adjusts the number of worker threads.
    void manager_thread();

    std::map<std::thread::id, std::thread> workers; // All worker threads
    std::vector<std::thread::id> ids; // Thread IDs to be removed by the manager
    std::thread manager_; // Manager thread

    std::atomic<int> current_threads_; // Number of current threads
    std::atomic<int> idle_threads_;    // Number of idle threads
    std::atomic<int> min_threads_;     // Minimum number of threads
    std::atomic<int> max_threads_;     // Maximum number of threads

    std::queue<std::function<void()>> tasks; // Task queue

    std::mutex queue_mutex; // Mutex for task queue
    std::condition_variable condition; // Condition variable for task notification
    std::atomic<bool> stop; // Stop flag
};

// Constructor: initialize thread pool with min_threads worker threads and start manager thread
inline ThreadPool::ThreadPool(size_t min_threads, size_t max_threads)
    : stop(false),
      current_threads_(0),
      idle_threads_(0),
      min_threads_(static_cast<int>(min_threads)),
      max_threads_(static_cast<int>(max_threads))
{
    for (size_t i = 0; i < min_threads; ++i) {
        std::thread t(&ThreadPool::worker_thread, this);
        workers.emplace(t.get_id(), std::move(t));
        ++current_threads_;
    }
    std::cout << "[ThreadPool] Initial worker threads: " << min_threads << std::endl;
    manager_ = std::thread(&ThreadPool::manager_thread, this);
}

// Worker thread main loop: fetch and execute tasks, handle dynamic removal
inline void ThreadPool::worker_thread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(this->queue_mutex);
            ++idle_threads_;
            // Wait until there is a task in the queue or the thread pool is stopped
            this->condition.wait(lock, [this] {
                return this->stop || !this->tasks.empty();
            });
            --idle_threads_;
            if (this->stop && this->tasks.empty())
                break;
            if (!this->tasks.empty()) {
                task = std::move(this->tasks.front());
                this->tasks.pop();
            } else {
                continue;
            }
        }
        if (task) task();
    }
    --current_threads_;
}

// Manager thread: periodically check and adjust the number of worker threads
inline void ThreadPool::manager_thread() {
    while (!stop) {
        std::this_thread::sleep_for(std::chrono::microseconds(100));
        int task_count = 0;
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            task_count = static_cast<int>(tasks.size());
        }
        int idle = idle_threads_;
        int curr = current_threads_;
        int min_thr = min_threads_;
        int max_thr = max_threads_;

        // Add threads if there are more tasks than idle threads and not at max
        if (task_count > idle && curr < max_thr) {
            int add = std::min(task_count - idle, max_thr - curr);
            if (add > 0) {
                std::cout << "[ThreadPool] Adding worker threads: " << add
                          << " (from " << curr << " to " << (curr + add) << ")" << std::endl;
            }
            for (int i = 0; i < add; ++i) {
                std::thread t(&ThreadPool::worker_thread, this);
                workers.emplace(t.get_id(), std::move(t));
                ++current_threads_;
            }
        }
        // Remove threads if there are more idle threads than tasks and above min
        if (idle > task_count && curr > min_thr) {
            int remove = std::min(idle - task_count, curr - min_thr);
            if (remove > 0) {
                std::cout << "[ThreadPool] Removing worker threads: " << remove
                          << " (from " << curr << " to " << (curr - remove) << ")" << std::endl;
                std::cout.flush();
            }
            for (int i = 0; i < remove; ++i) {
                // Notify idle threads to exit
                // Use ids mechanism to notify specific threads to exit
                {
                    std::lock_guard<std::mutex> lock(queue_mutex);
                    int count = 0;
                    for (int j = 0; j < remove; ++j) {
                        if (!workers.empty()) {
                            auto it = workers.begin();
                            // Advance iterator by j % workers.size() to select different threads for removal
                            std::advance(it, j % workers.size());
                            ids.push_back(it->first);
                            ++count;
                        }
                    }
                }
                condition.notify_all();
                break; // Only process once, avoid multiple notifications
            }
        }
    }
}

// Shutdown the thread pool: stop all threads and join them
inline void ThreadPool::shutdown() {
    stop = true;
    condition.notify_all();
    if (manager_.joinable())
        manager_.join();
    for (auto& pair : workers) {
        if (pair.second.joinable())
            pair.second.join();
    }
    workers.clear();
}

inline ThreadPool::~ThreadPool() {
    shutdown();
}

// Enqueue a task into the thread pool and return a future
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if (stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");
        tasks.emplace([task]() { (*task)(); });
    }
    condition.notify_one();
    return res;
}

#endif /* THREAD_POOL_H_ */