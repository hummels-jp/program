#include <queue>
#include <iostream>
#include <mutex>
#include <vector>
#include <functional>
#include <future>

using namespace std;


class ThreadPool
{

private:
    // construct function
    ThreadPool(size_t thread_count) : _stop(false)
    {
        for (size_t i = 0; i < thread_count; i++)
        {
            /* code */
            _workers.emplace_back(&ThreadPool::worker, this);
        }
        
    }

    // copy construct
    ThreadPool(const ThreadPool& other) = delete;

    // copy assignment
    ThreadPool& operator = (const ThreadPool& other) = delete;

public:

    // singleton, get the instance
    static ThreadPool& get_instance(size_t thread_count = 5)
    {
        static ThreadPool instance(thread_count);
        return instance; 
    }

    // deconstruct function
    ~ThreadPool()
    {
        {
            unique_lock<mutex> lock(_mutex);
            _stop = true;
        }
        _cv.notify_all();
        // thread can not be copy ,only can be reference or move
        for (auto& worker: _workers)
        {
            /* code */
            if (worker.joinable())
            {
                /* code */
                worker.join();
            }
            
        }
        
    }

    // add task into task queue
    // return type future<ReturnType>
    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args) -> future<decltype(f(args...))>
    {
        using ReturnType = decltype(f(args...));
        auto bind_func = bind(forward<F>(f), forward<Args>(args)...);

        packaged_task<ReturnType()> task(bind_func);

        auto task_ptr = make_shared<packaged_task<ReturnType()>>(std::move(task)); 

        future<ReturnType> _future = task_ptr->get_future();
        {
            unique_lock<mutex> lock(_mutex);
            if (_stop.load() == true)
            {
                /* code */
                throw runtime_error("thread pool stopped");
            }

            _tasks.emplace([task_ptr](){
                // add the call back function
                (*task_ptr)();
            });  
        }

        _cv.notify_one();

        return _future;
    }

private:

    vector<thread> _workers;
    queue<function<void()>> _tasks;
    mutex _mutex;
    condition_variable _cv;
    // bool _stop;
    atomic<bool> _stop;

    // task function
    void worker()
    {
        while (true)
        {
            /* code */
            function<void()> task;
            {
                unique_lock<mutex> lock(_mutex);
                // wait until _tasks.empty() != false or _stop = true
                _cv.wait(lock, [this](){
                    return (_stop.load() == true) || (_tasks.empty() == false);
                });

                if (_stop.load() == true && _tasks.empty()==true)
                {
                    /* code */
                    return;
                }

                task = std::move(_tasks.front());
                _tasks.pop();
            }

            task();
        }
        
    }
};

int add(int a, int b)
{
    return a + b;
}

int power(int a)
{
    return a*a;
}

int main()
{
    // ThreadPool pool(4);
    ThreadPool& pool = ThreadPool::get_instance(4);

    // auto f1 = pool.submit([](int a, int b) { return a + b; }, 1, 2);
    // auto f2 = pool.submit([](string s) { return s + " world!"; }, string("hello"));

    // cout << "f1 result: " << f1.get() << endl;
    // cout << "f2 result: " << f2.get() << endl;

    // auto f3 = pool.submit(add, 3, 4);
    // cout << "f3 result " << f3.get() << endl;

    // add multiple task
    vector<future<int>> _futures;
    for (int i = 0; i < 10; i++)
    {
        /* code */
        auto f = pool.submit(power, i);
        // _futures.push_back(std::move(f));
        _futures.emplace_back(std::move(f));
    }

    for (auto& f: _futures)
    {
        /* code */
        cout << "task results: " << f.get() << endl;

    }
    
    

    return 0;
}
