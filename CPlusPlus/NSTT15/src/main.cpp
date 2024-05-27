#include <container.h>

int main() {
  Container<int, char, Point> d(12, 'c', Point(2, 3));
  
  std::cout << d.getElement<int>(0) << std::endl;
  std::cout << d.getElement<char>(1) << std::endl;
  std::cout << d.getElement<Point>(2).x << " " << d.getElement<Point>(2).y
            << std::endl;

  return 0;
}
