#include <unordered_map>
#include <queue>
#include <utility>

class FreqStack {
public:
    //queue({frequency of value, {position of value, value}}, ...)
    std::priority_queue<std::pair<int, std::pair<int, int>>> prior_queue;
    std::unordered_map<int, int> freq;
    int pos = 0;


    FreqStack() {

    }

    void push(int val) {
        prior_queue.emplace(++freq[val], std::make_pair(++pos, val));
    }

    int pop() {
        auto elem = prior_queue.top();
        int val = elem.second.second;
        freq[val]--;
        prior_queue.pop();
        return val;
    }
};