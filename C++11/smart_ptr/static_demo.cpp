
#include <iostream>
using namespace std;

class Account
{

private:
    /* data */

public:
    Account(/* args */);
    ~Account();
    static double m_rate;
    static void set_rate(double rate)
    {
        m_rate = rate;
    }

    static double get_rate()
    {
        return m_rate;
    }
};

Account::Account(/* args */)
{
}

Account::~Account()
{
}

double Account::m_rate = 8.0;

int main()
{
    Account::set_rate(9.0);
    cout << Account::get_rate() << endl;

    Account a1;
    a1.set_rate(10.0);
    cout << a1.get_rate() << endl;

    Account a2;
    cout << a2.get_rate() << endl;
    
    return 0;
}