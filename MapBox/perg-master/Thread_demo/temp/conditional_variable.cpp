#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
using namespace std;

mutex mtx; // mutex lock
condition_variable cv;
bool flag = false;

// 根据flag 确定相应的逻辑
void myprint(int i)
{
    unique_lock<mutex> lock(mtx);
    while (flag==false)
    {
        cout << this_thread::get_id() << " is in wait " << endl;
        // cv 会与mutex 锁共用，在程序内部，再使用 unique_lock 进行封装
        cv.wait(lock); //条件不成立， 进入wait状态，释放 mutex 锁，等待唤醒。
    }

    // 满足条件
    cout << this_thread::get_id()<<"-" << i << endl; 
}

// 更新flag 的值， 通知客户
void update_flag()
{
    unique_lock<mutex> lock(mtx);
    cout << "update flag" << endl;
    flag = true; // 更新flag的值
    cv.notify_all(); // 通知所有的等待线程
}

int main()
{
    // 创建10个打印子线程，全部会进入wait状态
    vector<thread> printbox;
    for (int i = 0; i < 10; i++)
    {
        /* code */
        printbox.emplace_back(thread(myprint, i));
    }

    // 更新flag 的线程必须在打印子线程之前执行。
    thread update(update_flag);
    update.join();

    // 用创建的子线程，阻塞主线程
    for (auto& p:printbox)
    {
        /* code */
        p.join();
    }

    
    
    
}
