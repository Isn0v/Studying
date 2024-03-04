#include "treap.cpp"
#include <iostream>
#include <string.h>

int main() {
    Treap<int> treap;
    treap.insert(5);


    Treap<int> other;
    other.insert(5);

    bool res = (treap == other);
    std::cout << res << std::endl;
    return 0;
}