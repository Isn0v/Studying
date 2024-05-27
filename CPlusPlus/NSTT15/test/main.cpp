#include <container.h>
#include <gtest/gtest.h>

struct MyStruct {
  int x;
  double y;
  constexpr MyStruct(int a, double b) : x(a), y(b) {}
};

TEST(Container, Basic) {
  Container<int, char, Point> d(12, 'c', Point(2, 3));

  EXPECT_EQ(d.getElement<int>(0), 12);
  EXPECT_EQ(d.getElement<char>(1), 'c');
  
  EXPECT_EQ(d.getElement<Point>(2).x, 2);
  EXPECT_EQ(d.getElement<Point>(2).y, 3);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}