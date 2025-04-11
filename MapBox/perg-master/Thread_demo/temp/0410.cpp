#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
using namespace std;

std::mutex mtx;
std::condition_variable cv;
static int num = 1;
bool flag = false;

void consumer_function()
{

}

void producer_function()
{

}

int main()
{
    
    thread producer_threads[5];
    thread consumer_threads[5];
    for (int  i = 0; i < 5; i++)
    {
        producer_threads[i] = thread(producer_function);
        consumer_threads[i] = thread(consumer_function);
        /* code */
    }


    for (int  i = 0; i < 5; i++)
    {
        /* code */
        producer_threads[i].join();
        consumer_threads[i].join();
    }
    
    
    
}