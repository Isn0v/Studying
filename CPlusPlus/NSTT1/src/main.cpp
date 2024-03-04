#include "treap.cpp"
#include <iostream>
#include <string.h>

int main() {
    Treap<int> treap;
    treap.insert(5);


    Treap<int> other;
    other.insert(5);

    std::cout << (treap == other) << std::endl;
    return 0;
}