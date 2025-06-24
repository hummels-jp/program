
template <typename T>
class MyClass {
public:
    MyClass(T value) : value_(value) {}
    
    T getValue() const {
        return value_;
    }

int main()
{
    return 0;
}