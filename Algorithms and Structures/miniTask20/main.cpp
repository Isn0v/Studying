#include <vector>
#include <algorithm>

class MinStack {
public:
    std::vector<std::pair<int, int>>* vec;

    MinStack() {
        vec = new std::vector<std::pair<int, int>>();
    }

    void push(int val) {
        if (vec->empty()){
            vec->push_back({val, val});
        } else {
            vec->push_back({val, std::min(val, this->getMin())});
        }
    }

    void pop() {
        vec->pop_back();
    }

    int top() {
        return vec->at(vec->size() - 1).first;
    }

    int getMin() {
        return vec->at(vec->size() - 1).second;
    }
};