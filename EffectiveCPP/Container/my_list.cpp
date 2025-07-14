#include <iostream>
using namespace std;

// 节点定义
template<typename T>
struct MyListNode {
    T data;
    MyListNode* prev;
    MyListNode* next;
    MyListNode(const T& d) : data(d), prev(nullptr), next(nullptr) {}
};

template <typename T>
class MyList;

// 迭代器定义
template<typename T>
class MyListIterator {
    MyListNode<T>* node;
public:
    MyListIterator(MyListNode<T>* n = nullptr) : node(n) {}
    T& operator*() const { return node->data; }
    T* operator->() const { return &(node->data); }
    MyListIterator& operator++() { node = node->next; return *this; }
    MyListIterator operator++(int) { MyListIterator tmp = *this; ++(*this); return tmp; }
    MyListIterator& operator--() { node = node->prev; return *this; }
    MyListIterator operator--(int) { MyListIterator tmp = *this; --(*this); return tmp; }
    bool operator==(const MyListIterator& rhs) const { return node == rhs.node; }
    bool operator!=(const MyListIterator& rhs) const { return node != rhs.node; }
    friend class MyList<T>;
};

// 链表定义
template<typename T>
class MyList {
private:
    MyListNode<T>* head;
    MyListNode<T>* tail;
    size_t sz;

public:
    using iterator = MyListIterator<T>;

    MyList() : head(nullptr), tail(nullptr), sz(0) {}
    ~MyList() { clear(); }

    void push_back(const T& value) {
        MyListNode<T>* node = new MyListNode<T>(value);
        if (!tail) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        ++sz;
    }

    void push_front(const T& value) {
        MyListNode<T>* node = new MyListNode<T>(value);
        if (!head) {
            head = tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
        ++sz;
    }

    void pop_back() {
        if (!tail) return;
        MyListNode<T>* tmp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete tmp;
        --sz;
    }

    void pop_front() {
        if (!head) return;
        MyListNode<T>* tmp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete tmp;
        --sz;
    }

    void clear() {
        while (head) pop_front();
    }

    size_t size() const { return sz; }
    bool empty() const { return sz == 0; }

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }
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