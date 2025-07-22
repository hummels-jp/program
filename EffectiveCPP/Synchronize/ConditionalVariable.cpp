#include <iostream>
#include <condition_variable>
#include <thread>
#include <queue>
using namespace std;

const int _max_capacity = 5;
queue<int> _wharehouse;
mutex _mutex;
condition_variable cv_producer, cv_consumer;

void producer(int id)
{
    int product = 0;
    while (product < 10)
    {
        /* code */
        unique_lock<mutex> lock(_mutex);
        cv_producer.wait(lock, [](){
            return _wharehouse.size() < _max_capacity;
        });

        _wharehouse.push(product);
        cout << "Producer " << id << "produced product " << product << " current capacity is " << _wharehouse.size() << endl;
        product++;

        cv_consumer.notify_one();
    }
    
}

void consumer(int id)
{
    int consume_count = 0;
    while (consume_count < 10)
    {
        /* code */
        unique_lock<mutex> lock(_mutex);
        cv_consumer.wait(lock, [](){
            return _wharehouse.size() > 0;
        });

        int item = _wharehouse.front();
        _wharehouse.pop();

        cout << "consumer " << id << " consumed product " << item << " current capacity is " << _wharehouse.size() << endl;
        consume_count ++;

        cv_producer.notify_one();
    }
    
}

int main()
{
    thread p1(producer, 1);
    // thread p2(producer, 2);
    thread c1(consumer, 1);
    // thread c2(consumer, 2);

    p1.join();
    // p2.join();
    c1.join();
    // c2.join();
    return 0;
}