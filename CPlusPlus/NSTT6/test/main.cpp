#include "gtest/gtest.h"
#include <SquareMatrix.h>

TEST(SquareMatrixTest, ConstructsWithSize)
{
    SquareMatrix<int> matrix(3);
    ASSERT_EQ(matrix.get_size(), 3);
}

TEST(SquareMatrixTest, ConstructsFromDiagonal)
{
    int* diagonal = new int[3]{1, 2, 3};
    SquareMatrix<int> matrix(diagonal, 3);
    ASSERT_EQ(matrix[0][0], 1);
    ASSERT_EQ(matrix[1][1], 2);
    ASSERT_EQ(matrix[2][2], 3);
}

TEST(SquareMatrixTest, CopyConstructor)
{
    SquareMatrix<int> original(2);
    SquareMatrix<int> copy = original;
    ASSERT_TRUE(copy == original);
}

TEST(SquareMatrixTest, AddsMatrices)
{
    SquareMatrix<int> matrix1(2, 1);
    SquareMatrix<int> matrix2(2, 2);
    SquareMatrix<int> sum = matrix1 + matrix2;

    ASSERT_TRUE(sum == SquareMatrix<int>(2, 3));
}

TEST(SquareMatrixTest, MultipliesByMatrix)
{
    SquareMatrix<int> matrix1(2, 1);
    SquareMatrix<int> matrix2(2, 2);
    SquareMatrix<int> expected(2, 4);
    SquareMatrix<int> result = matrix1 * matrix2;
    ASSERT_EQ(result, expected);

    SquareMatrix<int> matrix3(2, 1);
    int scalar = 2;
    SquareMatrix<int> expected2(2, 2);
    SquareMatrix<int> result2 = matrix3 * scalar;
    ASSERT_EQ(result2, expected2);

    SquareMatrix<int> matrix4(2, 1);
    SquareMatrix<int> matrix5(3, 2);
    ASSERT_THROW(matrix4 * matrix5, std::invalid_argument);

    SquareMatrix<int> matrix6(2, 1);
    SquareMatrix<int> emptyMatrix;
    ASSERT_THROW(matrix6 * emptyMatrix, std::invalid_argument);

    SquareMatrix<int> emptyMatrix2;
    SquareMatrix<int> matrix7(2, 2);
    ASSERT_THROW(emptyMatrix2 * matrix7, std::invalid_argument);
}

TEST(SquareMatrixTest, EqualityOperator)
{
    SquareMatrix<int> matrix1(2, 0);
    SquareMatrix<int> matrix2(2, 0);
    ASSERT_TRUE(matrix1 == matrix2);
}

TEST(SquareMatrixTest, InequalityOperator)
{
    SquareMatrix<int> matrix1(2, 0);
    SquareMatrix<int> matrix2(3, 0);
    ASSERT_TRUE(matrix1 != matrix2);
}

TEST(SquareMatrixTest, MoveConstructor)
{
    SquareMatrix<int> original(2, 3);
    SquareMatrix<int> moved(std::move(original));
    ASSERT_EQ(moved.get_size(), 2);
    ASSERT_TRUE(moved == SquareMatrix<int>(2, 3));
}

TEST(SquareMatrixTest, DoubleConversion)
{
    SquareMatrix<int> matrix(2, 2);
    double scalar = static_cast<double>(matrix);
    ASSERT_EQ(scalar, 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
