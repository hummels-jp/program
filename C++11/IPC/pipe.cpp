#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#define pipe(fds) _pipe(fds, 4096, _O_BINARY)
#define read _read
#define write _write
#define close _close
#define WEXITSTATUS(x) x
#endif

int main() {
    // 创建管道
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        std::cerr << "管道创建失败" << std::endl;
        return 1;
    }

    std::cout << "管道创建成功 (read_fd=" << pipe_fd[0] 
              << ", write_fd=" << pipe_fd[1] << ")" << std::endl;

    // 创建子进程
    pid_t pid = fork();

    if (pid < 0) {
        // fork失败
        std::cerr << "fork失败" << std::endl;
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return 1;
    } 
    else if (pid == 0) {
        // 子进程代码
        close(pipe_fd[1]);  // 关闭写端，子进程只读

        char buffer[100];
        memset(buffer, 0, sizeof(buffer));
        
        std::cout << "子进程: 等待从管道读取数据..." << std::endl;
        
        // 从管道读取数据
        ssize_t bytes_read = read(pipe_fd[0], buffer, sizeof(buffer) - 1);
        
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';  // 确保字符串结束
            std::cout << "子进程: 从管道读取到数据: '" << buffer << "'" << std::endl;
            
            // 处理接收到的数据
            std::string received(buffer);
            std::string response = "子进程确认收到: " + received;
            
            // 打印处理结果
            std::cout << "子进程: 处理数据完成" << std::endl;
        } else {
            std::cerr << "子进程: 读取管道时出错" << std::endl;
        }
        
        close(pipe_fd[0]);  // 关闭读端
        return 0;
    } 
    else {
        // 父进程代码
        close(pipe_fd[0]);  // 关闭读端，父进程只写

        // 暂停一小段时间，确保子进程已经准备好接收数据
        sleep(1);
        
        const char* message = "Hello from parent process!";
        std::cout << "父进程: 正在向管道写入消息: '" << message << "'" << std::endl;
        
        // 向管道写入数据
        ssize_t bytes_written = write(pipe_fd[1], message, strlen(message));
        
        if (bytes_written < 0) {
            std::cerr << "父进程: 写入管道时出错" << std::endl;
            close(pipe_fd[1]);
            return 1;
        }
        
        std::cout << "父进程: 成功写入 " << bytes_written << " 字节到管道" << std::endl;
        close(pipe_fd[1]);  // 关闭写端
        
        // 等待子进程结束
        int status;
        waitpid(pid, &status, 0);
        
        std::cout << "父进程: 子进程已退出，状态码: " 
                  << WEXITSTATUS(status) << std::endl;
    }

    return 0;
}