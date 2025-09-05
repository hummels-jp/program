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
    // 1 get the message queue
    key_t key = ftok("/tmp", 65);
    int msgid = msgget(key, 0666|IPC_CREAT);
    if(msgid < 0)
    {
        perror("msgget failed");
        return -1;
    }

    // 2 send message to queue
    msg_buffer message;
    message.msg_type = 1;
    strcpy(message.msg_text, "hello from client");

    int result = msgsnd(msgid, &message, sizeof(message.msg_text), 0);
    if(result == -1)
    {
        perror("msgsnd failed");
        return -1;
    }
    cout << "client send message " << endl;


    return 0;
}