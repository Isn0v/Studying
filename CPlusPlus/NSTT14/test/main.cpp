#include <allocate.h>
#include <gtest/gtest.h>

struct MyStruct {
  int x;
  double y;
  constexpr MyStruct(int a, double b) : x(a), y(b) {}
};

TEST(Allocate, AllocateMethodTest) {
  constexpr int SIZE = 100;
  constexpr int N = 3;
  constexpr double PI = 3.14;
  char memory[SIZE];
  allocate<SIZE>(memory, N);
  int *ptr = reinterpret_cast<int *>(memory);
  EXPECT_EQ(*ptr, N);
}

TEST(Allocate, AllocateMethodTest2) {
  constexpr int SIZE = 100;
  constexpr int N = 3;
  constexpr double PI = 3.14;
  constexpr double E = 2.71;
  char memory[SIZE];
  allocate<SIZE>(memory, N, PI, E);
  int *ptr = reinterpret_cast<int *>(memory);
  EXPECT_EQ(*ptr, N);
  double *doublePtr = reinterpret_cast<double *>(memory + sizeof(int));
  EXPECT_DOUBLE_EQ(*doublePtr, PI);
  doublePtr = reinterpret_cast<double *>(memory + sizeof(int) + sizeof(double));
  EXPECT_DOUBLE_EQ(*doublePtr, E);
}

TEST(Allocate, AllocateMethodTest3) {
  constexpr int SIZE = 100;
  constexpr int N = 3;
  constexpr double PI = 3.14;
  constexpr double E = 2.71;
  char smallMemory[10];
  EXPECT_THROW(allocate<10>(smallMemory, N, PI, E), std::bad_alloc);
}

TEST(Allocate, AllocateMethodTest4) {
  constexpr int SIZE = 100;
  constexpr int N = 3;
  constexpr double PI = 3.14;
  constexpr MyStruct myStruct(42, 3.14);
  char memory[SIZE];
  allocate<sizeof(MyStruct)>(memory, myStruct);
  MyStruct *structPtr = reinterpret_cast<MyStruct *>(memory);
  EXPECT_EQ(structPtr->x, myStruct.x);
  EXPECT_DOUBLE_EQ(structPtr->y, myStruct.y);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}