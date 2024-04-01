#include "gtest/gtest.h"
#include "../src/SquareMatrix.h"

TEST(SquareMatrixTest, EqualityOperator) {
    SquareMatrix matrix1(2);
    matrix1.set(0, 0, 1.0);
    matrix1.set(0, 1, 2.0);
    matrix1.set(1, 0, 3.0);
    matrix1.set(1, 1, 4.0);

    SquareMatrix matrix2(2);
    matrix2.set(0, 0, 1.0);
    matrix2.set(0, 1, 2.0);
    matrix2.set(1, 0, 3.0);
    matrix2.set(1, 1, 4.0);

    EXPECT_EQ(matrix1, matrix2);

    matrix2.set(0, 0, 5.0);

    EXPECT_NE(matrix1, matrix2);
}

TEST(SquareMatrixTest, AdditionOperator) {
    SquareMatrix matrix1(2);
    matrix1.set(0, 0, 1.0);
    matrix1.set(0, 1, 2.0);
    matrix1.set(1, 0, 3.0);
    matrix1.set(1, 1, 4.0);

    SquareMatrix matrix2(2);
    matrix2.set(0, 0, 5.0);
    matrix2.set(0, 1, 6.0);
    matrix2.set(1, 0, 7.0);
    matrix2.set(1, 1, 8.0);

    SquareMatrix expected(2);
    expected.set(0, 0, 6.0);
    expected.set(0, 1, 8.0);
    expected.set(1, 0, 10.0);
    expected.set(1, 1, 12.0);

    EXPECT_EQ(matrix1 + matrix2, expected);
}

TEST(SquareMatrixTest, MultiplicationOperator) {
    SquareMatrix matrix1(2);
    matrix1.set(0, 0, 1.0);
    matrix1.set(0, 1, 2.0);
    matrix1.set(1, 0, 3.0);
    matrix1.set(1, 1, 4.0);

    SquareMatrix matrix2(2);
    matrix2.set(0, 0, 5.0);
    matrix2.set(0, 1, 6.0);
    matrix2.set(1, 0, 7.0);
    matrix2.set(1, 1, 8.0);

    SquareMatrix expected(2);
    expected.set(0, 0, 19.0);
    expected.set(0, 1, 22.0);
    expected.set(1, 0, 43.0);
    expected.set(1, 1, 50.0);

    EXPECT_EQ(matrix1 * matrix2, expected);
}

TEST(SquareMatrixTest, ScalarMultiplicationOperator) {
    SquareMatrix matrix(2);
    matrix.set(0, 0, 1.0);
    matrix.set(0, 1, 2.0);
    matrix.set(1, 0, 3.0);
    matrix.set(1, 1, 4.0);

    SquareMatrix expected(2);
    expected.set(0, 0, 2.0);
    expected.set(0, 1, 4.0);
    expected.set(1, 0, 6.0);
    expected.set(1, 1, 8.0);

    EXPECT_EQ(matrix * 2.0, expected);
}

// Add more tests as needed...


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}