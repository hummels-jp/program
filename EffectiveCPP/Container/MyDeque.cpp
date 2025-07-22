#include <iostream>
using namespace std;

template<typename T>
class MyDeque
{

private:
    T* _data;
    int _capacity;
    int _size;
    int _front;
    int _back;

    // reallocate the memory
    void resize(int new_capacity)
    {
        T* new_data = new T[new_capacity];
        for (int i = 0; i < _size; i++)
        {
            /* code */
            new_data[i] = _data[i];
        }
        delete []_data;
        _data = new_data;
        _capacity = new_capacity;
        _front = 0;
        _back = _size;   
    }

public:
    // construct function
    MyDeque(int capacity = 10): 
        _capacity(capacity), 
        _size(0), 
        _front(0), 
        _back(0)
    {
        _data = new T[_capacity];
    }

    // deconstuct function
    ~MyDeque()
    {
        delete []_data;
    }

    // get the element count in Deque
    int size()
    {
        return _size;
    }

    // wheather the Deque is empty
    bool empty()
    {
        return _size == 0;
    }

    // push_back, add an element into the deque by back
    void push_back(const T& value)
    {
        if (_size == _capacity)
        {
            /* code */
            resize(_capacity*2);
        }
        else
        {
            _data[_back] = value;
            _back = (_back + 1) % _capacity;
            
            _size ++;
        }
        
    }
    // push_front, add an element into the deque by front
    void push_front(const T& value)
    {
        if (_size == _capacity)
        {
            /* code */
            resize(_capacity*2);
        }
        else
        {
            _front = (_front -1 + _capacity)%_capacity;
            _data[_front] = value;
            _size ++;
        }
        
    }
    // pop_back, remove an element from the deque by back
    void pop_back()
    {
        if (_size == 0)
        {
            /* code */
            return;
        }
        else
        {
            _back = (_back - 1 + _capacity) % _capacity;
            _size --;
        }
        
    }

    // pop_front, remove an element from the deque by front
    void pop_front()
    {
        if (_size == 0)
        {
            /* code */
            return;
        }
        else
        {
            _front = (_front + 1 )%_capacity;
            _size --;
        }
        
    }

    // get the element by index, override operator []
    T& operator[](int index)
    {
        if (index < 0 || index >= _size)
        {
            /* code */
            cout << "input error index " << endl;
            return;
        }
        else
        {
            return _data[(_front + index) % _capacity];
        }
        
    }
};

int main() {
    MyDeque<int> dq;
    dq.push_back(1);
    dq.push_back(2);
    dq.push_front(0);
    dq.push_back(3);

    cout << "Deque内容: ";
    for (int i = 0; i < dq.size(); ++i)
        cout << dq[i] << " ";
    cout << endl;

    dq.pop_front();
    dq.pop_back();

    cout << "弹出后: ";
    for (int i = 0; i < dq.size(); ++i)
        cout << dq[i] << " ";
    cout << endl;

    return 0;
}