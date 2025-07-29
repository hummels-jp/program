#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>
using namespace std;

class ThreadPool {
public:
    // 单例获取接口
    static ThreadPool& instance(size_t thread_count = 4) {
        static ThreadPool pool(thread_count);
        return pool;
    }

    // 禁止拷贝和赋值
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    template<class F, class... Args>
    auto submit(F&& f, Args&&... args) -> future<decltype(f(args...) )> {
        using RetType = decltype(f(args...));
        auto task_ptr = make_shared<packaged_task<RetType()>>(
            bind(forward<F>(f), forward<Args>(args)...)
        );
        future<RetType> res = task_ptr->get_future();
        {
            lock_guard<mutex> lock(mtx_);
            if (stop_.load()) throw runtime_error("ThreadPool stopped");
            tasks_.emplace([task_ptr]() { (*task_ptr)(); });
        }
        cv_.notify_one();
        return res;
    }

    ~ThreadPool() {
        {
            lock_guard<mutex> lock(mtx_);
            stop_.store(true);
        }
        cv_.notify_all();
        for (auto& t : workers_) {
            if (t.joinable()) t.join();
        }
    }

private:
    ThreadPool(size_t thread_count) : stop_(false) {
        for (size_t i = 0; i < thread_count; ++i) {
            workers_.emplace_back(&ThreadPool::worker, this);
        }
    }

    void worker() {
        while (true) {
            function<void()> task;
            {
                unique_lock<mutex> lock(mtx_);
                cv_.wait(lock, [this] { return stop_.load() || !tasks_.empty(); });
                if (stop_.load() && tasks_.empty()) return;
                task = move(tasks_.front());
                tasks_.pop();
            }
            task();
        }
    }

    vector<thread> workers_;
    queue<function<void()>> tasks_;
    mutex mtx_;
    condition_variable cv_;
    std::atomic<bool> stop_; // 修改为原子变量
};

int main() {
    // 获取单例线程池
    ThreadPool& pool = ThreadPool::instance(4);

    auto f1 = pool.submit([](int a, int b) { return a + b; }, 1, 2);
    auto f2 = pool.submit([](string s) { return s + " world!"; }, string("hello"));

    cout << "f1 result: " << f1.get() << endl;
    cout << "f2 result: " << f2.get() << endl;

    // 提交多个任务
    vector<future<int>> results;
    for (int i = 0; i < 8; ++i) {
        results.push_back(pool.submit([i] { return i * i; }));
    }
    for (auto& f : results) {
        cout << "task result: " << f.get() << endl;
    }
    return 0;
}