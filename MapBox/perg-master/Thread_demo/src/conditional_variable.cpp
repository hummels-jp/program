#include<vector>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<iostream>
using namespace std;
#include "conditional_variable.h"

static int num = 0;
static mutex mtx;
static condition_variable cv;
static bool ready = false;

void f1()
{
    // create 10 threads, but each thread will wait for the condition variable
    cout << "Thread Type1: waiting for the condition variable" << this_thread::get_id() << endl;

    unique_lock<mutex> lck(mtx); // gets the mutex
    // 
    // while (ready ==false) // wait until ready is true
    // {
    //     cv.wait(lck); // releases the mutex and waits
    // }
    // wati ready to be true, releases the mutex and waits
    cv.wait(lck, [] { return ready; }); // releases the mutex and waits

    cout << "Thread 1: " << num << "finished" << endl;
    
}

void update()
{
    {
        lock_guard<mutex> lck(mtx); // gets the mutex
        num = 42; // update the shared variable
        ready = true; // set the condition to true
    }
    // cv.notify_all(); // notify all waiting threads
    // cv.notify_one(); // notify one waiting thread
}

int conditional_variable_demo()
{
    vector<thread> threads(10);
    for (int i = 0; i < 10; ++i)
    {
        threads[i] = thread(f1); // create threads
    }

    thread t(update); // create a thread to update the shared variable
    t.join(); // wait for the update thread to finish

    for (int  i = 0; i < 10; i++)
    {
        /* code */
        threads[i].join(); // wait for all threads to finish
    }


    return 0;
}