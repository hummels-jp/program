#include <memory>
#include <mutex>
#include <iostream>
#include <map>
using namespace std;

namespace SingletonTemplate
{
    template <typename T>
    class Singleton
    {

    private:
        static shared_ptr<T> _instance;
        static once_flag _flag;

        Singleton() = delete;
        ~Singleton() = delete;
        Singleton(const Singleton& other) = delete;
        Singleton& operator = (const Singleton& other) = delete;

public:
        template <typename ...Args>
        static shared_ptr<T> get_instance(Args... args)
        {
            std::call_once(_flag, [&](){
                _instance = make_shared<T>(std::forward<Args>(args)...);
            });

            return _instance;
        }
    };

    template <typename T>
    shared_ptr<T> Singleton<T>::_instance = nullptr;

    template <typename T>
    once_flag Singleton<T>::_flag;
}


class Point
{
private: 
    int _x;
    int _y;
public:
    Point(int x=0, int y =0)
        : _x(x)
        , _y(y)
    {

    }

friend class PointKey;
};

struct PointKey
{
    int _x, _y;
    PointKey(int x =0, int y =0): _x(x), _y(y)
    {
            
    }
    /* data */
    bool operator < (const PointKey& other)
    {

        if (_x < other._x || (_x == other._x && _y < other._y))
        {
            /* code */
            return true;
        }
        else
        {
            return false;
        }
        
    }
};

class PointDivider
{
private:
    static map<PointKey, shared_ptr<Point>> _instances;
    static mutex _mutex;

public:
    static shared_ptr<Point> get_instance(int x, int y)
    {
        PointKey key{x, y};
        lock_guard lock(_mutex);
        auto it = _instances.find(key);
        if (it != _instances.end())
        {
            /* code */
            return it->second;
        }
        else
        {
            auto ptr = make_shared<Point>(x, y);
            // auto ptr = SingletonTemplate::Singleton<Point>::get_instance(x, y);
            _instances[key] = ptr;
            return ptr;
        }
        
    }
};

map<PointKey, shared_ptr<Point>> PointDivider::_instances;
mutex PointDivider::_mutex;


int main()
{
    auto p1 = PointDivider::get_instance(1,2);
    auto p2 = PointDivider::get_instance(1,2);
    auto p3 = PointDivider::get_instance(3,4);
    cout << "p1 address: " << p1.get() << endl;
    cout << "p2 address: " << p2.get() << endl;
    cout << "p3 address: " << p3.get() << endl;
    return 0;
}