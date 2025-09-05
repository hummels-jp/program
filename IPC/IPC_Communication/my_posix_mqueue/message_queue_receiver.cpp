#include <iostream>
#include <mqueue.h>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
using namespace std;

int main()
{
    //1 open or create the mqueue file
    const char* queue_name = "/my_posix_mq";
    mqd_t mq = mq_open(queue_name, O_WRONLY | O_CREAT, 0666, nullptr);
    if(mq = (mqd_t) -1)
    {
        perror("mq_open failed ");
        return -1;
    }

    // 2 read from mqueue 
    char buffer[1024] = {0};
    ssize_t 

}