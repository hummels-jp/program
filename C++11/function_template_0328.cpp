#include <iostream>

// 将类名从 time 改为 Time，避免与标准库冲突
class Time 
{
public:
    // 构造函数
    Time(int hour = 0, int minute = 0, int second = 0) 
        : m_hour(hour), m_minute(minute), m_second(second) 
    {}

    // 运算符重载：小于
    bool operator<(const Time& t) const 
    {
        if (m_hour < t.m_hour)
            return true;
        else if (m_hour == t.m_hour) 
        {
            if (m_minute < t.m_minute)
                return true;
            else if (m_minute == t.m_minute) 
            {
                if (m_second < t.m_second)
                    return true;
            }
        }
        return false;
    }

    // 运算符重载：大于
    bool operator>(const Time& t) const 
    {
        if (m_hour > t.m_hour)
            return true;
        else if (m_hour == t.m_hour) 
        {
            if (m_minute > t.m_minute)
                return true;
            else if (m_minute == t.m_minute) 
            {
                if (m_second > t.m_second)
                    return true;
            }
        }
        return false;
    }

    // 打印时间（便于测试）
    void print() const 
    {
        std::cout << m_hour << ":" << m_minute << ":" << m_second << std::endl;
    }

private:
    int m_hour;
    int m_minute;
    int m_second;
};

// 函数模板：最大值
template <class T>
inline const T& max(const T& a, const T& b) 
{
    return a > b ? a : b;
}

// 函数模板：最小值
template <class T>
inline const T& min(const T& a, const T& b) 
{
    return a < b ? a : b;
}

int main() 
{
    Time t1(12, 30, 45); // 修改类名为 Time
    Time t2(13, 15, 30);

    std::cout << "t1: ";
    t1.print();
    std::cout << "t2: ";
    t2.print();

    std::cout << "Max time: ";
    max(t1, t2).print();

    std::cout << "Min time: ";
    min(t1, t2).print();

    return 0;
}