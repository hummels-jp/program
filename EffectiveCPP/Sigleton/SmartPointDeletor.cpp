#include <iostream>
#include <memory>
using namespace std;

class Point
{
private:
    int _x;
    int _y;

    ~Point()
    {
        cout << "private ~Point " << endl;
    }

public:
    Point(int x =0, int y =0)   
        : _x(x)
        , _y(y)
    {

    }

friend class PointDeletor;
};

class PointDeletor
{
public:
    void operator()(Point* p) const
    {
        delete p;
    }
};

int main()
{
    unique_ptr<Point, PointDeletor> uptr(new Point(1,2));

    shared_ptr<Point> sptr(new Point(3,4), PointDeletor());


    return 0;
}