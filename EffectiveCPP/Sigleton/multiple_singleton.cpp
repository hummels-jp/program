#include <iostream>
#include <memory>
#include <map>
#include <mutex>
using namespace std;

// 多例模式（Multiton）：根据不同key返回唯一实例
class Config {
public:
    Config(const string& name) : _name(name) {
        cout << "Config(" << _name << ") 构造" << endl;
    }
    void show() const { cout << "Config: " << _name << endl; }
private:
    string _name;
};

class ConfigMultiton {
public:
    static shared_ptr<Config> getInstance(const string& name) {
        lock_guard<mutex> lock(_mtx);
        auto it = _instances.find(name);
        if (it != _instances.end()) {
            return it->second;
        } else {
            auto ptr = make_shared<Config>(name);
            _instances[name] = ptr;
            return ptr;
        }
    }
private:
    static map<string, shared_ptr<Config>> _instances;
    static mutex _mtx;
};

map<string, shared_ptr<Config>> ConfigMultiton::_instances;
mutex ConfigMultiton::_mtx;

int main() {
    auto c1 = ConfigMultiton::getInstance("db");
    auto c2 = ConfigMultiton::getInstance("db");
    auto c3 = ConfigMultiton::getInstance("log");

    c1->show();
    c3->show();

    cout << "c1地址: " << c1.get() << endl;
    cout << "c2地址: " << c2.get() << endl;
    cout << "c3地址: " << c3.get() << endl;
    cout << "c1 == c2? " << (c1 == c2 ? "yes" : "no") << endl;
    cout << "c1 == c3? " << (c1 == c3 ? "yes" : "no") << endl;
    return 0;
}