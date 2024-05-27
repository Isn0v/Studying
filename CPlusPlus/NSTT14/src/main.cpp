#include <allocate.h>


int main() {

  constexpr int SIZE = 64;
  constexpr int N = 3;
  constexpr double PI = 3.14;
  constexpr char C = 'a';

  char memory[SIZE];
  allocate<SIZE>(memory, N, PI, C);

  size_t offset = 0;

  std::cout << *(reinterpret_cast<int *>(memory)) << std::endl; // 3
  offset += sizeof(int);
  std::cout << *(reinterpret_cast<double *>(memory + offset))
            << std::endl; // 3.14
  offset += sizeof(double);
  std::cout << *(reinterpret_cast<char *>(memory + offset)) << std::endl; // a

  return 0;
}
