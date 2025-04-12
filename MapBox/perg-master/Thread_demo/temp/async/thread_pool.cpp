#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

// 任务函数（普通函数）
int exampleTask(int id) {
    std::cout << "任务 " << id << " 开始执行\n";
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟耗时任务
    std::cout << "任务 " << id << " 执行完成\n";
    return id * id;
}

// 线程池类
class ThreadPool {
public:
    // 构造函数，初始化线程池
    ThreadPool(size_t numThreads) {
        start(numThreads);
    }

    // 停止线程池
    ~ThreadPool() {
        stop();
    }

    // 提交任务到任务队列
    // Func 是用户传入的函数类型，Args 是函数参数类型 
    // future 的返回值类型是函数的返回值类型
    // std::future<decltype(func(args...))> 用于获取函数返回值的类型
    template <typename Func, typename... Args>
    auto enqueue(Func&& func, Args&&... args) -> std::future<decltype(func(args...))> 
    {
        // 定义用户传入的函数的返回类型
        // decltype(func(args...)) 用于获取函数返回值的类型
        using ReturnType = decltype(func(args...));

        // 包装任务为 std::packaged_task
        // std::packaged_task 用于将函数和参数封装成一个可调用对象 
        // std::bind 用于绑定函数和参数， 将用户传入的函数和参数绑定到一起，得到一个返回值为 ReturnType， 参数为空的函数对象
        // auto task = std::make_shared<std::packaged_task<ReturnType()>>(std::bind(func, args...));
        // std::forward 用于完美转发参数，保持参数的值类别
        auto task = std::make_shared<std::packaged_task<ReturnType()>>(std::bind(std::forward<Func>(func), 
        std::forward<Args>(args)...));

        {
            std::unique_lock<std::mutex> lock(mEventMutex);
            // 如果线程池已经停止，则抛出异常
            if (mStopping) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            // 插入任务到任务队列
            mTasks.emplace([task]() {
                (*task)();
            });
        }

        // 通知线程有新任务
        mEventVar.notify_one();

        // 返回一个 std::future 对象，用于获取任务的结果
        // std::future 是一个异步操作的结果的占位符
        return task->get_future();
    }

private:
    std::vector<std::thread> mThreads;           // 线程池中的线程
    std::condition_variable mEventVar;           // 条件变量
    std::mutex mEventMutex;                      // 互斥锁
    bool mStopping = false;                      // 是否停止线程池
    std::queue<std::function<void()>> mTasks;    // 任务队列,任务是一个可调用对象， 返回值为 void，参数为空
    // 任务队列是一个先进先出（FIFO）的队列，存储待执行的任务
    // 任务是一个 std::function<void()> 对象，表示一个无参数、无返回值的可调用对象
    // 这里使用 std::function 来存储任务，允许存储任意可调用对象（函数指针、lambda 表达式、函数对象等）
    // 任务队列是线程安全的，使用互斥锁来保护对任务队列的访问
    // 互斥锁用于保护对任务队列的访问，确保线程安全

    // 启动线程池
    void start(size_t numThreads) 
    {
        for (size_t i = 0; i < numThreads; ++i) {
            // this 指针传递给线程函数，确保每个线程都能访问到线程池对象
            mThreads.emplace_back(&ThreadPool::workerThread, this); // 向线程池添加工作线程
        }
    }

    // 工作线程函数
    void workerThread() 
    {
        while (true) {
            std::function<void()> task;

            {
                std::unique_lock<std::mutex> lock(mEventMutex);

                // 等待新任务或线程池停止
                mEventVar.wait(lock, [this] { return mStopping || !mTasks.empty(); });

                if (mStopping && mTasks.empty()) {
                    break;
                }

                // 获取任务
                task = std::move(mTasks.front());
                mTasks.pop();
            }

            // 打印当前线程 ID
            std::cout << "线程 " << std::this_thread::get_id() << " 开始执行任务\n";

            // 执行任务
            task();

            // 打印任务完成信息
            std::cout << "线程 " << std::this_thread::get_id() << " 完成任务\n";
        }
    }

    // 停止线程池
    void stop() noexcept {
        // 设置停止标志
        {
            std::unique_lock<std::mutex> lock(mEventMutex);
            mStopping = true;
        }

        // 通知所有线程
        mEventVar.notify_all();

        // 等待所有线程完成，将所有线程加入到主线程，以防止主线程提前退出
        for (auto &thread : mThreads) {
            thread.join();
        }
    }
};

// 函数对象（Functors）
struct TaskFunctor {
    int operator()(int id) const {
        std::cout << "任务 " << id << " 开始执行 (函数对象)\n";
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟耗时任务
        std::cout << "任务 " << id << " 执行完成 (函数对象)\n";
        return id * id;
    }
};

int main() {
    // 创建线程池，包含 4 个线程
    ThreadPool pool(4);

    // 提交普通函数任务
    for (int i = 0; i < 4; ++i) {
        pool.enqueue(exampleTask, i);
    }

    // 提交函数对象任务
    TaskFunctor functor;
    for (int i = 4; i < 8; ++i) {
        pool.enqueue(functor, i);
    }

    // 主线程等待一段时间，确保所有任务完成
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "所有任务已完成\n";

    return 0;
}