#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main()
{
    // 1 create 5 child process
    // wait for the 3 child process
    int i = 0;
    int childpid = 0;
    for (i = 0; i < 5; i++)
    {
        /* code */
        int pid = fork();
        if (-1 == pid)
        {
            /* code */
            cout << "fork failed " << endl;
        }
        else if (0 == pid)
        {
            sleep(1);
            /* code */
            cout << "child process " << i + 1 << " created : " <<  getpid() << endl;
            // can not create child process nested
            return i;
        }
        else if (pid > 0)
        {
            /* code */
            // at the fork function, the child pid is return in the parent process
            if (i == 3)
            {
                /* code */
                childpid = pid;
                cout << "in child, before wait, 3 child pid is " << childpid << endl;
            }
            
        }

    }

    if (i == 5)
    {
        /* code */
        // wait(NULL);
        // int status = 0;
        // cout << "in parent, before waitpid, childpid is " << childpid << endl; 
        // // pid_t wait_pid = waitpid(childpid, &status, 0); // wait with blocked
        // pid_t wait_pid = waitpid(childpid, &status, WNOHANG); // wait with no blocked
        // if (-1 == wait_pid)
        // {
        //     /* code */
        //     cerr << "waitpid failed" << endl;
        //     return 1;
        // }
        // else if (0 == wait_pid)
        // {
        //     /* code */
        //     cerr << "child was not finished" << endl;
        //     return 1;
        // }
        

        // cout << "parent wait for child pid "  << wait_pid << endl;
        // if (WIFEXITED(status))
        // {
        //     /* code */
        //     cout << "child exit with return " << WEXITSTATUS(status) << endl;
        // }
        
        
        // cout << "parent pid " << getpid() << endl;

        // wait for all the child process
        pid_t wait_pid = 0;
        int status = 0;
        // wait child process in the block mode
        // while ((wait_pid = waitpid(-1, &status, 0)) > 0) 
        // {
        //     /* code */
        //     cout << "wait child pid " << wait_pid << " finished " << endl;
        // }

        // wait child process in the unblock mode
        while (true)
        {
            /* code */
            wait_pid = waitpid(-1, &status, WNOHANG);
            if (wait_pid == 0)
            {
                /* code */
                cout << "no child process finished " << endl;
                sleep(1);
            }
            else if (wait_pid > 0)
            {
                /* code */
                cout << "child process finished: " << wait_pid << endl;  
            }
            else
            {
                cout << "no child process exist " << endl;
                break;
            }  
        }
        
        
    }
    
    
    return 0;
}