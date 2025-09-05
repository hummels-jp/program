#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
using namespace std;

// Define message buffer structure
struct msg_buffer {
	long msg_type;
	char msg_text[100];
};

int main()
{
    // 1 create message queue
    key_t key = ftok("/tmp", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if(msgid < 0)
    {
        perror("msgget failed ");
        return -1;
    }

    msg_buffer message;
    cout << "Server: waiting for message: " << endl;

    // 2 receive message for type 1;
    int message_type = 1;
    msgrcv(msgid, &message, sizeof(message.msg_text), message_type, 0);
    cout << "received message: " << message.msg_text << endl;

    // 3 close the message queue
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}