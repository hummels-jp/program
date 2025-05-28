// 1 定义数组
// 2 定义数组的大小
// 3 数组元素查找
// 4 数组元素插入
// 5 数组元素删除
// 6 数组元素遍历
// 7 数组元素排序
// 8 数组元素反转
// 9 数组元素去重
// 10 数组元素合并
// 11 数组元素交集
// 12 数组元素差集
// 13 数组元素并集
// 14 数组元素子集
// 15 末尾增加元素
// 16 头部增加元素
// 17 中间增加元素
// 18 末尾删除元素
// 19 头部删除元素
// 20 中间删除元素

#include <iostream>
#include <time.h>
using namespace std;

class Array {
    public:
        // construct function
        Array(int capacity=10)
            : m_capacity(capacity)
            , m_current(0)
        {
            m_array = new int[m_capacity];
        }

        // destruct function
        ~Array()
        {
            delete [] m_array;
            m_array = nullptr;
        }

        // insert an element in the pos
        bool insert_element(int pos, int value)
        {
            if (pos < 0 || pos > m_current)
            {
                /* code */
                throw "insert pos is wrong";
            }

            // array is full, need to expand
            if (m_current ==m_capacity)
            {
                expand_array(m_capacity*2);
            }

            int i = m_current;
            while (i>pos)
            {
                /* code */
                m_array[i+1] = m_array[i];
                i--;
            }
            m_array[pos] = value;

            m_current +=1;

            return true;
        }

        // show array
        void show()
        {
            for (int  i = 0; i < m_current; i++)
            {
                /* code */
                cout << m_array[i] << " ";
            }
            cout << endl;
        }

        // get the current number of items
        int get_current()
        {
            return m_current;
        }

        // find an defined value, the first one 
        int find(int value)
        {
            for (int i = 0; i < m_current; i++)
            {
                if (m_array[i] == value)
                {
                    /* code */
                    return i;
                }
                
            }

            return -1;
            
            
        }

    private: 
        // expand the array
        bool expand_array(int size)
        {
            if (size <=m_capacity)
            {
                /* code */
                return false;
            }

            int* new_array = new int[size];
            memcpy(new_array, m_array, m_capacity*sizeof(int));
            delete []m_array;
            m_array = new_array;
            m_capacity = size;
            
            return true;
        }

    private:
        int* m_array; // point to an address which can be extended;
        int m_capacity; // array capacity
        int m_current; // current array item count;
};

int main()
{
    srand(time(0));

    int capacity = 10;
    Array array(10);

    for (int i = 0; i < capacity; i++)
    {
        /* code */
        array.insert_element(i, rand()%100);
    }

    array.show();
    
    cout << array.get_current() << endl;

    array.insert_element(0, 100);
    array.show();

    array.insert_element(array.get_current(), 200);
    array.show();

    return 0;
}