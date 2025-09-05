#include <iostream>
#include <mqueue.h>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
using namespace std;

int main()
{
    // 1 open the mqueue file
    const char* mqueue_file = "/my_posix_mq";
    mqd_t mq = mq_open(mqueue_file, O_WRONLY| O_CREAT, 0666, nullptr);
    if(mq ==(mqd_t)-1)
    {
        perror("mq_open failed");
        return -1;
    }

    // 2 send message to the mqueue
    const char* message = "Hello from sender via posix mqueue ";
    int result = mq_send(mq, message, strlen(message) + 1, 0);
    if(result == -1)
    {
        perror("mq_send failed");
        mq_close(mq);
        return -1;
    }
    cout << "Sender: message send " << endl;

    // 3 close the mqueue
    mq_close(mq);
    
    return 0;
}