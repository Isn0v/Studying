#include <iostream>

template <typename... Types> class Container {
private:
  void *memory;

public:
  Container(Types... args) {
    size_t size = (0 + ... + sizeof(Types));

    memory = new char[size];

    auto assign = [&, offset = 0](auto arg) mutable {
      decltype(arg) *ptr = (decltype(arg) *)((char *)memory + offset);
      *ptr = arg;
      offset += sizeof(decltype(arg));
    };

    (assign(args), ...);
  }

  ~Container() { delete[] memory; }

  template <typename T> T getElement(size_t index) {
    if (index >= sizeof...(Types)) {
      throw std::out_of_range("Index out of range");
    }

    size_t cur_index = 0;
    size_t offset = (0 + ... + (cur_index++ < index ? sizeof(Types) : 0));

    T *ptr = (T *)((char *)memory + offset);
    return *ptr;
  }
};

struct Point {
  int x;
  int y;

  Point(int x, int y) : x(x), y(y) {}

  double getX() const { return x; }
  double getY() const { return y; }
};

int main() {
  int a = 12;
  char b = 'c';
  Point c(2, 3);
  Container<int, char, Point> d(a, b, c);

  std::cout << d.getElement<int>(0) << std::endl;
  std::cout << d.getElement<char>(1) << std::endl;
  std::cout << d.getElement<Point>(2).x << " " << d.getElement<Point>(2).y
            << std::endl;

  return 0;
}
