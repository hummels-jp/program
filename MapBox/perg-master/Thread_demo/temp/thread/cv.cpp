#include<condition_variable>
#include<mutex>
#include<thread>
#include<iostream>
using namespace std;


bool has_package_flag = false;
mutex g_mtx;
condition_variable cv;

void package_reciver()
{
    for (int i = 0; i < 10; i++)
    {
        unique_lock<mutex> lock(g_mtx);
        // while (has_package_flag == false) 
        // {
        //     /* code */
        //     cv.wait(lock);
        // }
        // 将while循环转换为 lamada表达式
        cv.wait(lock, [&](){return has_package_flag==true;});

        has_package_flag = false;
        cv.notify_all();
        cout << "going to get package " << i << endl;
        this_thread::sleep_for(std::chrono::milliseconds(300));
    }  
}

void package_spot()
{
    for (int i = 0; i < 10; i++)
    {
        unique_lock<mutex> lock(g_mtx);
        // while (has_package_flag == true)  // 如果有包裹，等待接收器处理完
        // {
        //     /* code */
        //     cv.wait(lock);
        // }
        cv.wait(lock, [&](){return has_package_flag==false;});

        has_package_flag = true;
        cv.notify_all();
        cout << "received package" << i << endl;
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    

}

int main()
{
    thread reciver(package_reciver);
    thread spot(package_spot);
    spot.join();
    reciver.join();
    
    
    return 0;
}

