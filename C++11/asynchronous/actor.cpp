#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
#include <functional>
#include <string>
#include <unordered_map>
#include <atomic>

// 消息基类
class Message {
public:
    virtual ~Message() = default;
    virtual std::string getType() const = 0;
};

// Actor基类
class Actor {
private:
    // 消息队列和同步原语
    std::queue<std::shared_ptr<Message>> mailbox;
    std::mutex mutex;
    std::condition_variable cv;
    std::thread worker;
    std::atomic<bool> running;

protected:
    // 处理消息的虚函数，由子类实现
    virtual void receive(std::shared_ptr<Message> message) = 0;
    
public:
    Actor() : running(false) {}
    
    virtual ~Actor() {
        stop();
    }

    // 启动Actor
    void start() {
        std::lock_guard<std::mutex> lock(mutex);
        if (!running) {
            running = true;
            worker = std::thread(&Actor::processMessages, this);
        }
    }

    // 停止Actor
    void stop() {
        {
            std::lock_guard<std::mutex> lock(mutex);
            running = false;
            cv.notify_all();
        }

        if (worker.joinable()) {
            worker.join();
        }
    }

    // 发送消息给Actor
    void send(std::shared_ptr<Message> message) {
        {
            std::lock_guard<std::mutex> lock(mutex);
            mailbox.push(message);
        }
        cv.notify_one();
    }

private:
    // 消息处理循环
    void processMessages() {
        while (true) {
            std::shared_ptr<Message> message;
            {
                std::unique_lock<std::mutex> lock(mutex);
                cv.wait(lock, [this] {
                    return !running || !mailbox.empty();
                });

                if (!running && mailbox.empty()) {
                    break;
                }

                message = mailbox.front();
                mailbox.pop();
            }

            receive(message);
        }
    }
};

// Actor系统 - 管理所有Actor
class ActorSystem {
private:
    std::unordered_map<std::string, std::shared_ptr<Actor>> actors;
    std::mutex mutex;
    static ActorSystem* instance;

    ActorSystem() = default;

public:
    static ActorSystem& getInstance() {
        static ActorSystem instance;
        return instance;
    }

    // 注册Actor
    void registerActor(const std::string& name, std::shared_ptr<Actor> actor) {
        std::lock_guard<std::mutex> lock(mutex);
        actors[name] = actor;
        actor->start();
    }

    // 获取Actor
    std::shared_ptr<Actor> getActor(const std::string& name) {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = actors.find(name);
        if (it != actors.end()) {
            return it->second;
        }
        return nullptr;
    }

    // 向Actor发送消息
    void send(const std::string& actorName, std::shared_ptr<Message> message) {
        auto actor = getActor(actorName);
        if (actor) {
            actor->send(message);
        } else {
            std::cerr << "Actor not found: " << actorName << std::endl;
        }
    }

    // 关闭所有Actor
    void shutdown() {
        std::lock_guard<std::mutex> lock(mutex);
        for (auto& pair : actors) {
            pair.second->stop();
        }
        actors.clear();
    }
};

// 具体消息类型
class TextMessage : public Message {
private:
    std::string content;

public:
    TextMessage(const std::string& content) : content(content) {}

    std::string getContent() const {
        return content;
    }

    std::string getType() const override {
        return "TextMessage";
    }
};

class MathMessage : public Message {
private:
    int a, b;
    std::string operation;

public:
    MathMessage(int a, int b, const std::string& operation)
        : a(a), b(b), operation(operation) {}

    int getA() const { return a; }
    int getB() const { return b; }
    std::string getOperation() const { return operation; }

    std::string getType() const override {
        return "MathMessage";
    }
};

// 具体Actor实现
class PrinterActor : public Actor {
protected:
    void receive(std::shared_ptr<Message> message) override {
        if (message->getType() == "TextMessage") {
            auto textMsg = std::dynamic_pointer_cast<TextMessage>(message);
            std::cout << "PrinterActor received: " << textMsg->getContent() << std::endl;
        } else {
            std::cout << "PrinterActor received unknown message type: " << message->getType() << std::endl;
        }
    }
};

// 数学计算Actor
class MathActor : public Actor {
private:
    std::shared_ptr<Actor> resultReceiver;

public:
    void setResultReceiver(std::shared_ptr<Actor> receiver) {
        resultReceiver = receiver;
    }

protected:
    void receive(std::shared_ptr<Message> message) override {
        if (message->getType() == "MathMessage") {
            auto mathMsg = std::dynamic_pointer_cast<MathMessage>(message);
            int result = 0;
            
            if (mathMsg->getOperation() == "add") {
                result = mathMsg->getA() + mathMsg->getB();
                std::cout << "MathActor calculated: " << mathMsg->getA() << " + " 
                          << mathMsg->getB() << " = " << result << std::endl;
            } else if (mathMsg->getOperation() == "multiply") {
                result = mathMsg->getA() * mathMsg->getB();
                std::cout << "MathActor calculated: " << mathMsg->getA() << " * " 
                          << mathMsg->getB() << " = " << result << std::endl;
            }

            // 将结果发送到结果接收器
            if (resultReceiver) {
                resultReceiver->send(std::make_shared<TextMessage>(
                    "Result: " + std::to_string(result)));
            }
        } else {
            std::cout << "MathActor received unknown message type" << std::endl;
        }
    }
};

// 日志Actor
class LogActor : public Actor {
protected:
    void receive(std::shared_ptr<Message> message) override {
        std::cout << "LogActor: Logged message of type " << message->getType() << std::endl;
        
        if (message->getType() == "TextMessage") {
            auto textMsg = std::dynamic_pointer_cast<TextMessage>(message);
            std::cout << "Log content: " << textMsg->getContent() << std::endl;
        }
    }
};

int main() {
    // 获取Actor系统实例
    auto& system = ActorSystem::getInstance();
    
    // 创建Actors
    auto printer = std::make_shared<PrinterActor>();
    auto mathActor = std::make_shared<MathActor>();
    auto logger = std::make_shared<LogActor>();
    
    // 设置MathActor的结果接收器
    mathActor->setResultReceiver(printer);
    
    // 注册Actors到系统
    system.registerActor("printer", printer);
    system.registerActor("math", mathActor);
    system.registerActor("logger", logger);
    
    // 发送消息
    system.send("printer", std::make_shared<TextMessage>("Hello, Actor World!"));
    system.send("logger", std::make_shared<TextMessage>("System initialized"));
    system.send("math", std::make_shared<MathMessage>(5, 3, "add"));
    system.send("math", std::make_shared<MathMessage>(4, 7, "multiply"));
    
    // 等待消息处理完成
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // 关闭Actor系统
    system.shutdown();
    
    return 0;
}