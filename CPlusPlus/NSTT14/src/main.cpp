#include <cstddef>
#include <iostream>
#include <new>     // for placement new
#include <utility> // for forward

template <size_t SIZE, typename... Types>
constexpr void allocate(void *memory, Types &&...args) {
  size_t requiredSize = (0 + ... + sizeof(std::decay_t<Types>));
  bool typesCopyConstructible = (... && std::is_copy_constructible_v<Types>);

  if (requiredSize > SIZE && !typesCopyConstructible) {
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
  constexpr int N = 3;
  constexpr double PI = 3.14;
  constexpr char C = 'a';

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
