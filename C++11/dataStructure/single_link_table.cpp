
// 1 创建单链表
// 2 遍历单链表
// 3 插入节点，尾插法
// 4 插入节点，头插法
// 5 删除节点
// 6 查找节点
// 7 反转单链表
// 8 合并两个有序单链表
// 9 删除链表的倒数第k个节点
// 10 判断链表是否有环
// 11 求链表的中间节点
// 12 求链表的长度
// 13 单链表是否有环，环的起始节点
// 14 求两个链表的交点
// 15 求链表的交点，环的起始节点

#include <iostream>
#include <time.h>
using namespace  std;



class  single_link_node
{
public:
    single_link_node(int data=0)
    : m_data(data)
    , m_next(nullptr)
    {
    }

    ~single_link_node()
    {
        m_next = nullptr;
    }

    int m_data;
    single_link_node* m_next;
};

class single_link_table
{
public:
    single_link_table()
    {
        m_head = new single_link_node();
    }

    ~single_link_table()
    {
        single_link_node* cur = m_head;
        while (cur != nullptr)
        {
            /* code */
            single_link_node* tmp = cur;
            cur = cur->m_next;
            delete tmp;
        } 
    }

    // insert item
    bool insert_head(int value)
    {
        single_link_node* new_node = new single_link_node(value);
        new_node->m_next = m_head->m_next;
        m_head->m_next = new_node;

        return true;
    }

    bool insert_tail(int value)
    {
        single_link_node* new_node = new single_link_node(value);

        single_link_node* tail_node = m_head;
        while(tail_node->m_next != nullptr)
        {
            tail_node = tail_node->m_next;
        }
        tail_node->m_next = new_node;
        return true;
    }

    void show()
    {
        single_link_node* cur = m_head->m_next;
        while (cur != nullptr)
        {
            /* code */
            cout << cur->m_data << " ";
            cur = cur->m_next;
        }
        cout << endl;
        
    }
    
private:
    single_link_node* m_head;
};

int main()
{
    // single_link_table table;
    // table.insert_head(1);
    // table.insert_head(2);
    // table.insert_head(3);
    // table.insert_head(4);
    // table.insert_head(5);
    // table.show();

    single_link_table table;
    table.insert_tail(1);
    table.insert_tail(2);
    table.insert_tail(3);
    table.insert_tail(4);
    table.insert_tail(5);
    table.show();
    
    return 0;
}

