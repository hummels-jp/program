#include <iostream>
#include <memory>
#include <string>

// 抽象接口
class Subject {
public:
    virtual void request() const = 0;
    virtual ~Subject() = default;
};

// 实际对象
class RealSubject : public Subject {
public:
    void request() const override {
        std::cout << "RealSubject: Handling request." << std::endl;
    }
};

// 代理对象
class Proxy : public Subject {
private:
    // 使用智能指针管理资源，避免内存泄漏
    mutable std::shared_ptr<RealSubject> realSubject; // 使用 mutable 允许在 const 方法中修改
    std::string accessLevel;

public:
    explicit Proxy(const std::string& level) : accessLevel(level) {}

    void request() const override {
        // 检查访问权限
        if (checkAccess()) {
            // 延迟加载实际对象
            if (!realSubject) {
                // 这里可以添加更多的初始化逻辑
                realSubject = std::make_shared<RealSubject>();
            }
            realSubject->request();
        } else {
            std::cout << "Proxy: Access denied. Insufficient permissions." << std::endl;
        }
    }

private:
    bool checkAccess() const {
        std::cout << "Proxy: Checking access for level: " << accessLevel << std::endl;
        return accessLevel == "admin"; // 只有管理员权限才能访问
    }
};

// 客户端代码
int main() {
    std::cout << "Client: Accessing with user level:\n";
    Proxy userProxy("user");
    userProxy.request();

    std::cout << "\nClient: Accessing with admin level:\n";
    Proxy adminProxy("admin");
    adminProxy.request();

    return 0;
}