#include <array>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <condition_variable>
using namespace std;

mutex mtx;
condition_variable cv;
const int max_vector_size = 10; // 队列最大长度
mutex command_mtx; // 互斥量，用于保护命令行输出

class ThreadSafeQueue
{
public:
    void put(int value)
    {
        unique_lock<mutex> lock(mtx); // 锁住互斥量
        // while (m_vec.size() >= max_vector_size) // 如果队列已满
        // {

        //     cout <<  "producer wait for space " << endl;
        //     cv.wait(lock); // 等待条件变量通知
        // }
        cv.wait(lock, [&](){return m_vec.size() < max_vector_size;}); // 等待条件变量通知
        
        m_vec.push(value);
        cv.notify_all();
    }

    int get()
    {
        unique_lock<mutex> lock(mtx);
        // while (m_vec.empty())
        // {

        //     cout << "consumer wait for item " << endl;
        //     cv.wait(lock); // 等待条件变量通知
        // }
        cv.wait(lock, [&](){return m_vec.size() > 0;}); // 等待条件变量通知

        int value = m_vec.front();
        m_vec.pop();
        cv.notify_all();
        
        return value;
    }
private:
queue<int> m_vec;
};

void producer(ThreadSafeQueue& q)
{
    for (int i = 0; i < 10; i++)
    {
        unique_lock<mutex> command_lock(command_mtx); // 锁住命令行输出互斥量
        q.put(i);
        cout << "producer: " << i << endl;
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
}

void consumer(ThreadSafeQueue& q)
{
    for (int i = 0; i < 10; i++)
    {
        /* code */
        unique_lock<mutex> command_lock(command_mtx); // 锁住命令行输出互斥量
        int value = q.get();
        cout << "consumer " << value << endl;
        this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    
}

int main()
{
    ThreadSafeQueue q;
    thread t1(producer, std::ref(q));
    thread t2(consumer, std::ref(q));

    t1.join();
    t2.join();
    cout << "All done!" << endl;
    
    return 0;
}
