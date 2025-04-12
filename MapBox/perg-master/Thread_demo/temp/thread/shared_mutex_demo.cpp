#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>
using namespace std;

std::shared_mutex my_shared_mutex;

int shared_data = 0;

void reader(int id) {
    shared_lock lock(my_shared_mutex);
    cout << "reader " << id << " sees: " << shared_data << endl;

}

void writer(int id) {
    unique_lock lock(my_shared_mutex);
    shared_data++;
    cout << "writeer" << id << " update: " << shared_data << endl;
}

int main() {

    vector<thread> readers;
    for (int i = 0; i < 5; i++)
    {
        /* code */
        readers.emplace_back(thread(reader,i));
    }

    vector<thread> writers;
    for (int i = 0; i < 2; i++)
    {
        writers.emplace_back(writer,i);
    }

    for (auto& reader : readers)
    {
        /* code */
        reader.join();
    }

    for (auto& writer: writers)
    {
        writer.join();
    }
    
    
    return 0;
}
