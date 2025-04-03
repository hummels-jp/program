#include <iostream>
using namespace std;

// 抽象基类：饮料
class Beverage {
public:
    // 模板方法：定义制作饮料的步骤
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        if (customerWantsCondiments()) { // 钩子方法
            addCondiments();
        }
    }

    // 基本步骤：所有饮料都需要烧水
    void boilWater() {
        cout << "Boiling water" << endl;
    }

    // 基本步骤：所有饮料都需要倒入杯中
    void pourInCup() {
        cout << "Pouring into cup" << endl;
    }

    // 纯虚函数：由子类实现具体的冲泡方式
    virtual void brew() = 0;

    // 纯虚函数：由子类实现具体的添加调料方式
    virtual void addCondiments() = 0;

    // 钩子方法：子类可以选择是否添加调料
    virtual bool customerWantsCondiments() {
        return true; // 默认需要调料
    }

    virtual ~Beverage() = default;
};

// 子类：茶
class Tea : public Beverage {
public:
    void brew() override {
        cout << "Steeping the tea" << endl;
    }

    void addCondiments() override {
        cout << "Adding lemon" << endl;
    }
};

// 子类：咖啡
class Coffee : public Beverage {
public:
    void brew() override {
        cout << "Dripping coffee through filter" << endl;
    }

    void addCondiments() override {
        cout << "Adding sugar and milk" << endl;
    }

    // 重写钩子方法：不需要调料
    bool customerWantsCondiments() override {
        char answer;
        cout << "Would you like sugar and milk with your coffee (y/n)? ";
        cin >> answer;
        return (answer == 'y' || answer == 'Y');
    }
};

// 主函数
int main() {
    cout << "Making tea..." << endl;
    Tea tea;
    tea.prepareRecipe();

    cout << "\nMaking coffee..." << endl;
    Coffee coffee;
    coffee.prepareRecipe();

    return 0;
}