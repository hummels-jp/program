#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        // 子进程
        cout << "child process, pid=" << getpid() << endl;
        sleep(2);
        return 42;
    } else if (pid > 0) {
        // 父进程
        int status;
        pid_t child_pid = waitpid(pid, &status, 0); // 等待指定子进程
        cout << "parent waited for child pid=" << child_pid << endl;
        if (WIFEXITED(status)) {
            cout << "child exited with code " << WEXITSTATUS(status) << endl;
        }
    }
    return 0;
}

