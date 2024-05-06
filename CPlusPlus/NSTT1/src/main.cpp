#include "treap.cpp"
#include <iostream>
#include <string.h>


#include <stdexcept>

template <typename Derived, int Limit>
class InstanceLimiter {
private:
    static int instance_count;

protected:
    InstanceLimiter() {
        if (instance_count >= Limit) {
            throw std::runtime_error("Instance limit reached");
        }
        ++instance_count;
    }

    virtual ~InstanceLimiter() {
        --instance_count;
    }

public:
    InstanceLimiter(const InstanceLimiter&) = delete;
    InstanceLimiter& operator=(const InstanceLimiter&) = delete;

    static int getInstanceCount() {
        return instance_count;
    }
};

template <typename Derived, int Limit>
int InstanceLimiter<Derived, Limit>::instance_count = 0;

// Usage:
class MyClass : public InstanceLimiter<MyClass, 3> {
public:
    MyClass() : InstanceLimiter() {
        // Constructor logic here
    }

    ~MyClass() {
        // Destructor logic here
    }
};

int main() {
    // Treap<int> treap;
    // treap.insert(5);


    // Treap<int> other;
    // other.insert(5);

    // bool res = (treap == other);
    // std::cout << res << std::endl;
    try {
        MyClass a;
        MyClass b;
        MyClass c;
        // This will throw an exception because the limit is 3
        MyClass d;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    // return 0;
    return 0;
}