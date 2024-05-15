#pragma once
// #include "../test/main.cpp"


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