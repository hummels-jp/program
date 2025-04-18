#include <iostream>
#include <string>
#include <vector>
#include <memory>

// 观察者接口
class Observer {
public:
    virtual void update(const std::string& weather) = 0;
    virtual ~Observer() = default;
};

// 被观察者接口
class Subject {
public:
    virtual void attach(std::shared_ptr<Observer> observer) = 0;
    virtual void detach(std::shared_ptr<Observer> observer) = 0;
    virtual void notify() = 0;
    virtual ~Subject() = default;
};

// 具体的被观察者：Weather
class Weather : public Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;
    std::string currentWeather;

public:
    void setWeather(const std::string& weather) {
        currentWeather = weather;
        notify();
    }

    void attach(std::shared_ptr<Observer> observer) override {
        observers.push_back(observer);
    }

    void detach(std::shared_ptr<Observer> observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify() override {
        for (const auto& observer : observers) {
            observer->update(currentWeather);
        }
    }
};

// 具体观察者：TV
class TV : public Observer {
public:
    void update(const std::string& weather) override {
        std::cout << "TV: Weather update: " << weather << std::endl;
    }
};

// 具体观察者：Radio
class Radio : public Observer {
public:
    void update(const std::string& weather) override {
        std::cout << "Radio: Weather update: " << weather << std::endl;
    }
};

// 具体观察者：Newspaper
class Newspaper : public Observer {
public:
    void update(const std::string& weather) override {
        std::cout << "Newspaper: Weather update: " << weather << std::endl;
    }
};

// 客户端代码
int main() {
    auto weather = std::make_shared<Weather>();

    auto tv = std::make_shared<TV>();
    auto radio = std::make_shared<Radio>();
    auto newspaper = std::make_shared<Newspaper>();

    weather->attach(tv);
    weather->attach(radio);
    weather->attach(newspaper);

    std::cout << "Weather changes to Sunny:\n";
    weather->setWeather("Sunny");

    std::cout << "\nWeather changes to Rainy:\n";
    weather->setWeather("Rainy");

    return 0;
}