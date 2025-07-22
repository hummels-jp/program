#include <iostream>
#include <queue>
#include <condition_variable>
#include <atomic>
#include <cstddef>
using namespace std;

template <typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue(size_t capacity): _capacity(capacity)
    {

    }

    // 
    void push(const T& value)
    {
        unique_lock<mutex> lock(_mutex);
        cv_not_full.wait(lock, [](){
            return _queue.size() < _capacity;
        });

        _queue.push(value);   
        
        cv_not_empty.notify_one();
    )     
        
    }

    T& wait_and_pop(T& value)
    {
        unique_lock<mutex> lock(_mutex);
        cv_not_empty.wait(lock, [](){
            return _queue.size() > 0;
        });

        value = _queue.top();
        _queue.pop();
        cv_not_full.notify_one();

        return value;
    }
private:
    size_t _capacity;
    queue<T> _queue;
    mutex _mutex;
    condition_variable cv_not_full, cv_not_empty;
};

