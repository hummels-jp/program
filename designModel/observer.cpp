#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

// 抽象观察者
class Observer {
public:
    virtual ~Observer() = default;
    // 更新方法，接收主题的通知
    // 这里使用了 std::string 来传递消息，实际应用中可以根据需要修改为其他类型
    virtual void update(const std::string& message) = 0;
};

// 抽象主题
class Subject {
public:
    virtual ~Subject() = default;
    // 观察者注册和注销方法
    // 这里使用了 std::shared_ptr 来管理观察者的生命周期，避免内存泄漏
    virtual void attach(std::shared_ptr<Observer> observer) = 0;
    // 观察者注销方法
    // 这里使用了 std::shared_ptr 来管理观察者的生命周期，避免内存泄漏
    virtual void detach(std::shared_ptr<Observer> observer) = 0;
    // 通知所有观察者的方法
    virtual void notify() = 0;
};

// 具体主题
class ConcreteSubject : public Subject {
private:
    // 使用 std::vector 来存储观察者列表
    // 这里使用了 std::shared_ptr 来管理观察者的生命周期，避免内存泄漏
    std::vector<std::shared_ptr<Observer>> observers;
    // 使用 std::string 来存储消息
    std::string message;

public:
    void attach(std::shared_ptr<Observer> observer) override {
        observers.push_back(observer);
    }

    void detach(std::shared_ptr<Observer> observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify() override {
        for (const auto& observer : observers) {
            if (observer) {
            observer->update(message);
            }
        }
    }

    void createMessage(const std::string& newMessage) {
        message = newMessage;
        notify();
    }
};

// 具体观察者
class ConcreteObserver : public Observer {
private:
    std::string name;

public:
    explicit ConcreteObserver(const std::string& observerName) : name(observerName) {}

    void update(const std::string& message) override {
        std::cout << "Observer " << name << " received message: " << message << std::endl;
    }
};

// 测试代码
int main() {
    // 创建主题和观察者对象
    // 使用 std::make_shared 来创建智能指针，避免手动管理内存
    auto subject = std::make_shared<ConcreteSubject>();

    // 创建观察者对象
    // 使用 std::make_shared 来创建智能指针，避免手动管理内存
    auto observer1 = std::make_shared<ConcreteObserver>("Observer1");
    auto observer2 = std::make_shared<ConcreteObserver>("Observer2");

    subject->attach(observer1);
    subject->attach(observer2);
    // 创建消息并通知观察者
    subject->createMessage("Hello, Observers!");
    subject->detach(observer1);
    subject->createMessage("Another message!");

    return 0;
}