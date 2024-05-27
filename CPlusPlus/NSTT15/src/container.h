#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

template <std::size_t N, typename... Types>
using TypeAtIndex = typename std::tuple_element<N, std::tuple<Types...>>::type;

template <typename... Types> class Container {
private:
  char memory[(0 + ... + sizeof(Types))];

public:
  constexpr Container(Types &&...args) {

    auto assign = [&, offset = 0](auto arg) mutable {
      decltype(arg) *ptr = (decltype(arg) *)((char *)memory + offset);
      *ptr = arg;
      offset += sizeof(decltype(arg));
    };

    (assign(std::forward<Types>(args)), ...);
  }

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

  constexpr Point(int x, int y) : x(x), y(y) {}

  double getX() const { return x; }
  double getY() const { return y; }
};