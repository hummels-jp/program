#include <iostream>
using namespace std;

template<typename T>
class point
{
    public:
        point(T x, T y): m_x(x), m_y(y) {}
        void output()
        {
            cout << "x = " << m_x << ", y = " << m_y << endl;
        }
    private:
        T m_x, m_y;
};

int main()
{
    point<int> p1(1, 2);
    p1.output();
    point<double> p2(1.1, 2.2);
    p2.output();
    return 0;
}