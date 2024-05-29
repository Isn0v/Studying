#include "treap.h"
// #include "instance_limiter.h"
#include <iostream>
#include <stdexcept>
#include <string.h>

int main() {
  Treap<int> a;

  a.insert(10);
  a.insert(5);
  a.insert(15);


  auto it = a.iterator();
  while(it.hasNext()) {
    std::cout << it.next() << std::endl;
  }

    return 0;
}