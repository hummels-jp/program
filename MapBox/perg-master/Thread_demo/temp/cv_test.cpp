#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
using namespace std;

std::mutex mtx;
std::condition_variable cv;
const unsigned int MAX_BUFFER_SIZE = 5;

// STL 中的容器都是线程不安全的。
class ThreadSafeQuere
{
public:
    void put(int a)
    {
        unique_lock<mutex> lock(mtx); // mutex锁，访问共享资源
        while (m_queue.size()>=MAX_BUFFER_SIZE) // 生产者不符合条件，进入wait，释放锁
        {
            cv.wait(lock);
        }

        m_queue.push(a); // 生产者符合条件，执行操作，通知所有等待线程。
        cv.notify_all();
        cout << "producer: " << a << endl;
    }

    int get()
    {
        unique_lock<mutex> lock(mtx); // mutex锁， 访问共享资源
        while (m_queue.empty())
        {
            cv.wait(lock); // 消费者不符合条件，进入wait，释放锁
        }

        // cv.wait(lock, [$](){return m_queue.empty();})
        
        int value = m_queue.front();
        m_queue.pop();  // 消费者符合条件，执行操作，通知所有等待线程。
        cv.notify_all();
        cout << "consumer " << value << endl;
        return value;
    }
private:
    queue<int> m_queue;
};

// std::queue<int> buffer; // 共享数据



void producer(ThreadSafeQuere* q) {
    for (int i = 0; i < 10; i++)
    {
        q->put(i);
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
    
}

void consumer(ThreadSafeQuere* q) {
    for (int i = 0; i < 10; i++)
    {
        /* code */
        q->get();
        std::this_thread::sleep_for(std::chrono::microseconds(200));
    }
    
}

ThreadSafeQuere buffer;
int main() {
    
    std::thread p1(producer, &buffer);
    // std::thread p2(producer, &buffer);
    std::thread c1(consumer, &buffer);

    p1.join();
    c1.join();

    return 0;
}
