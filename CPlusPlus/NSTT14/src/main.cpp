#include <cstddef>
#include <iostream>
#include <new>     // for placement new
#include <utility> // for forward

template <size_t SIZE, typename... Types>
void allocate(void *memory, Types &&...args) {
  size_t requiredSize = (0 + ... + sizeof(std::decay_t<Types>));

  if (requiredSize > SIZE) {
    throw std::bad_alloc();
  }

  auto construct = [memory, offset = size_t{0}](auto &&arg) mutable {
    using T = std::decay_t<decltype(arg)>;
    void *ptr = static_cast<char *>(memory) + offset;
    new (ptr) T(std::forward<decltype(arg)>(arg)); // placement new
    offset += sizeof(T);
  };

  (..., construct(std::forward<Types>(args)));
}

int main() {

  constexpr int SIZE = 64;
  int N = 3;
  double PI = 3.14;
  char C = 'a';

  char memory[SIZE];
  allocate<SIZE>(memory, N, PI, C);

  size_t offset = 0;

  std::cout << *(reinterpret_cast<int *>(memory )) << std::endl; // 3
  offset += sizeof(int);
  std::cout << *(reinterpret_cast<double *>(memory + offset)) << std::endl; // 3.14
  offset += sizeof(double);
  std::cout << *(reinterpret_cast<char *>(memory + offset)) << std::endl; // a

  return 0;
}
