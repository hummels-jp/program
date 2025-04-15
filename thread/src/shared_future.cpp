#include <iostream>
#include <future>
#include <thread>
#include <vector>
using namespace std;

void computeSquare(std::promise<int> promise, int value) {
    promise.set_value(value * value);
}

void threadfucint2(shared_future<int> sharedFuture) {
    std::cout << "Thread function executed" << std::endl;
    cout << sharedFuture.get() << endl;
}

int main() {
    // Create a promise and future
    std::promise<int> promise;
    std::shared_future<int> sharedFuture = promise.get_future().share();

    // Launch a thread to compute the square of a number
    std::thread t(computeSquare, std::move(promise), 5);
    t.join();

    cout << sharedFuture.get() << endl; // Get the value from the shared future

    std::thread t2(threadfucint2, sharedFuture);
    t2.join(); // Wait for the thread to finish

    // Join all threads
    
    // for (auto& th : threads) {
    //     th.join();
    // }

    return 0;
}