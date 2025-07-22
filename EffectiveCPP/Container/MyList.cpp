// 自定义List 双向队列
#include <cstddef>
#include <iostream>
using namespace std;

// 定义节点
template<typename T>
struct MyListNode
{
    /* data */
    T _data;
    MyListNode* _prev;
    MyListNode* _next;

    MyListNode(const T& data): _data(data), _prev(nullptr), _next(nullptr)
    {

    }
};

// 声明 MyList
template <typename T>
class MyList;

// 定义迭代器
template<typename T>
class MyListIterator
{
private:
    MyListNode<T>* _node; //  迭代器本质上就是一个指向节点的指针。

public:
    //  consturct function
    MyListIterator(MyListNode<T>* node=nullptr):_node(node)
    {

    }

    // dereference function, return value is T&, override operator *
    T& operator*()
    {
        return _node->_data;
    }
    
    // address function, return value is T*, override operator ->
    T* operator ->()
    {
        return &(_node->_data);
    }

    // prefix increment function, return value is the new iterator, override operator ++
    MyListIterator& operator ++()
    {
        _node = _node->_next;
        return *this;
    }

    // postfix increment function, return value is the old iterator, override operator ++(int)
    MyListIterator operator++(int)
    {
        MyListIterator<T> old = *this;
        ++(*this);
        return old;
    }

    // prefix decrement function, return value is MyListIterator&, override operator --
    MyListIterator& operator --()
    {
        _node = _node->_prev;
        return *this;
    }

    // postfix decrement function, return value is MyListIterator, override operator --(int)
    MyListIterator operator--(int)
    {
        MyListIterator old = *this;
        --(*this);
        return old;
    }

    // == operator, wheather pointer to the same node
    bool operator==(const MyListIterator& other)
    {
        return _node == other._node;
    }

    // bool operator !=
    bool operator !=(const MyListIterator& other)
    {
        return _node != other._node;
    }

    // To visit the MyListItrearot in the MyList, 
    // MyList should be the friend class of MyListIterator
    friend class MyList<T>;

};

// 定义队列
template<typename T>
class MyList
{

    using iterator = MyListIterator<T>;

private:
    MyListNode<T>* _head; // point to the first element
    MyListNode<T>* _tail; // point to the last element
    size_t _size; // element count

public:
    // consturct function
    MyList():
        _head(nullptr),
        _tail(nullptr), 
        _size(0)
    {

    }

    // deconstruct function, because we have pointer member 
    ~MyList()
    {
        clear();
    }

    // push_back, add an element in the tail of list
    void push_back(const T& value)
    {
        MyListNode<T>* new_node = new MyListNode(value);
        if (_tail == nullptr)
        {
            /* code */
            _head = _tail = new_node;
        }
        else
        {
            _tail->_next = new_node;
            new_node->_prev = _tail;
            _tail = new_node;
        }

        _size++;
    }
    // push_front, add an element in the front of list
    void push_front(const T& value)
    {
        MyListNode<T>* new_node = new MyListNode(value);
        if (_head == nullptr)
        {
            /* code */
            _head = _tail = new_node;
        }
        else
        {
            new_node->_next = _head;
            _head->_prev = new_node;
            _head = new_node;
        }
        _size++;
    }

    // pop_back, remove an element in the back of list
    void pop_back()
    {
        if (_tail == nullptr)
        {
            /* code */
            return;
        }
        MyListNode<T>* tmp = _tail;
        _tail = _tail->_prev;

        // if the new tail is not empty
        if (_tail != nullptr)
        {
            /* code */
            _tail->_next = nullptr;
        }
        // if the new tail is empty, need to make head empty
        else
        {
            _head = nullptr;
        }

        delete tmp;
        _size --;
        
        
    }

    // pop_front, remove an element in the front of list
    void pop_front()
    {
        if (_head == nullptr)
        {
            /* code */
            return;
        }

        MyListNode<T>* tmp = _head;
        _head = _head->_next;
        if (_head!=nullptr)
        {
            /* code */
            _head->_prev = nullptr;

        }
        else
        {
            _tail = nullptr;
        }

        delete tmp;
        _size --;   
    }

    // remove all the element from the list
    void clear()
    {
        while (_head!=nullptr)
        {
            /* code */
            pop_front();
        }
        
    }

    // get element count in the list
    size_t getSize() const
    {
        return _size;
    }


    // whether the list is empty
    bool empty() const
    {
        return _size == 0;
    }

    // begin， get the head iterator
    MyListIterator<T> begin()
    {
        return MyListIterator<T>(_head);
    }

    // end, get the null iterator after tail
    MyListIterator<T> end()
    {
        return MyListIterator<T>(nullptr);
    }
};


int main() 
{
    MyList<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_front(0);

    cout << "正向遍历: ";
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    lst.pop_front();
    lst.pop_back();

    cout << "剩余元素: ";
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}
