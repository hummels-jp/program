#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <functional>
#include <future>
using namespace std;

class ThreadPool
{
private:
    vector<thread> _workers; 
    queue<function<void()>> _tasks;
    mutex _mutex;
    condition_variable _cv;
    atomic<bool> _stop;

    ThreadPool(int thread_count = 4)
    {
        // add thread to the thread pool
        for (int i = 0; i < thread_count; i++)
        {
            /* code */
            _workers.emplace_back(&ThreadPool::worker, this);
        }
        
    }

    // thread main function, get the task from the task queue and execute the callback function
    void worker()
    {
        while (true)
        {
            /* code */
            function<void()> task;
            {
                unique_lock<mutex> lock(_mutex);
                _cv.wait(lock, [this](){
                    return (_tasks.empty() == false) || (_stop.load() == true);
                });

                if (_stop.load() == true && _tasks.empty() == true)
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

public:
    // singleton 
    static ThreadPool& get_instance(int thread_count=4)
    {
        static ThreadPool pool(thread_count);
        return pool;
    }

    // deconstruct function
    ~ThreadPool()
    {
        // update _stop value
        {
            unique_lock<mutex> lock(_mutex);
            _stop.store(false);
        }
        _cv.notify_all();
        {
            // wait for all the thread finished
            for (auto& t: _workers)
            {
                /* code */
                if (t.joinable())
                {
                    /* code */
                    t.join();
                }
                
            }
            
        }
    }

    // add task to the task queue, 
    template<typename F, typename ... Args>
    auto submit(F&& f, Args&& ... args) -> future<decltype(f(args...))>
    {
        using ReturnType = decltype(f(args...));
        auto bind_func = bind(std::forward<F>(f), std::forward<Args>((args) ...);
        packaged_task<ReturnType()> task(bind_func);
        auto task_ptr = make_shared<packaged_task<ReturnType()>>(std::move(task));
        future<ReturnType> _future = task_ptr->get_future();
        {
            unique_lock<mutex> lock(_mutex);

            if (_stop.load() == true)
            {
                /* code */
                throw runtime_error("Thread Pool Stopped ");
            }

            _tasks.emplace([task_ptr](){
                (*task_ptr)();
            });  
        }

        _cv.notify_one();
        return _future;

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