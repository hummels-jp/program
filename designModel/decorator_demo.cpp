#include <iostream>
#include <string>
#include <memory>
using namespace std;

// 抽象接口类   
class Logger
{
public:
    virtual ~Logger() {};
    virtual void log(const std::string &message) = 0;
};

// 具体实现类1
class ConsoleLogger : public Logger
{
public:
    void log(const std::string &message) override
    {
        std::cout << "Console: " << message << std::endl;
    }
};

// 具体实现类2
class FileLogger : public Logger
{
public:
    void log(const std::string &message) override
    {
        std::cout << "File: " << message << std::endl;
    }
};

// 抽象装饰器类
class LoggerDecorator : public Logger
{
protected:
    std::unique_ptr<Logger> logger;
public:     
    LoggerDecorator(std::unique_ptr<Logger> logger) : logger(std::move(logger)) {}
    void log(const std::string &message) override
    {
        logger->log(message);
    }
};

// 具体装饰器类1
class TimestampLogger : public LoggerDecorator
{
public:
    TimestampLogger(std::unique_ptr<Logger> logger) : LoggerDecorator(std::move(logger)) {}
    
    // 重写log方法，添加时间戳功能
    void log(const std::string &message) override
    {
        std::cout << "[Timestamp] ";
        LoggerDecorator::log(message);
    }
};

// 具体装饰器类2
class LevelLogger : public LoggerDecorator
{   
public:
    LevelLogger(std::unique_ptr<Logger> logger) : LoggerDecorator(std::move(logger)) {}
    
    //  重写log方法，添加日志级别功能
    void log(const std::string &message) override
    {
        std::cout << "[Level] ";
        LoggerDecorator::log(message);
    }
};

int main()
{
    std::unique_ptr<Logger> consoleLogger = std::make_unique<ConsoleLogger>();
    std::unique_ptr<Logger> fileLogger = std::make_unique<FileLogger>();

    consoleLogger->log("Hello, World!");
    fileLogger->log("Hello, File!");

    std::cout << "------------------------" << std::endl;
    // 使用装饰器模式添加时间戳和日志级别功能   
    std::unique_ptr<Logger> timestampedConsoleLogger = std::make_unique<TimestampLogger>(std::move(consoleLogger));
    std::unique_ptr<Logger> levelFileLogger = std::make_unique<LevelLogger>(std::move(fileLogger));

    timestampedConsoleLogger->log("Hello, Decorator!");
    levelFileLogger->log("Hello, Decorator File!");

    std::cout << "------------------------" << std::endl;
    // 继续使用装饰器模式添加时间戳和日志级别功能
    std::unique_ptr<Logger> levelTimestampedConsoleLogger = std::make_unique<LevelLogger>(std::move(timestampedConsoleLogger));
    std::unique_ptr<Logger> timestampedLevelFileLogger = std::make_unique<TimestampLogger>(std::move(levelFileLogger)); 
    levelTimestampedConsoleLogger->log("Hello, Decorator with Level and Timestamp!");
    timestampedLevelFileLogger->log("Hello, Decorator File with Timestamp and Level!");

    return 0;
}