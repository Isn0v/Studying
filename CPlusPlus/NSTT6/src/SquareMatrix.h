#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class SquareMatrix
{
private:
    std::vector<std::vector<T>> data;
    size_t size;

public:
    size_t get_size() const
    {
        return size;
    }

    SquareMatrix(): size(0) {}

    explicit SquareMatrix(size_t size, T value = T{}) : size(size), data(size, std::vector<T>(size, value)) {}

    explicit SquareMatrix(const std::vector<T> &diagonal) : SquareMatrix(diagonal.size())
    {
        for (size_t i = 0; i < diagonal.size(); ++i)
        {
            data[i][i] = diagonal[i];
        }
    }

    SquareMatrix(const std::vector<std::vector<T>> &matrix)
    {
        if (matrix.size() != matrix[0].size())
        {
            throw std::invalid_argument("The matrix is not square.");
        }
        size = matrix.size();
        data = matrix;
    }

    SquareMatrix(const SquareMatrix &other)
        : size(other.size), data(other.data) {}

    SquareMatrix(SquareMatrix &&other) noexcept
        : size(std::move(other.size)), data(std::move(other.data)) {}

    SquareMatrix &operator=(const SquareMatrix &other)
    {
        if (this != &other)
        {
            size = other.size;
            data = other.data;
        }
        return *this;
    }

    SquareMatrix &operator=(SquareMatrix &&other) noexcept
    {
        if (this != &other)
        {
            size = std::move(other.size);
            data = std::move(other.data);
        }
        return *this;
    }

    ~SquareMatrix() = default;

    SquareMatrix operator+(const SquareMatrix &other) const
    {
        if (size != other.size)
        {
            throw std::invalid_argument("Matrices are not the same size.");
        }
        SquareMatrix result(size);
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < size; ++j)
            {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    SquareMatrix &operator+=(const SquareMatrix &other)
    {
        if (size != other.size)
        {
            throw std::invalid_argument("Matrices are not the same size.");
        }
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < size; ++j)
            {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }

    SquareMatrix operator*(const SquareMatrix &other) const
    {
        if (size != other.size)
        {
            throw std::invalid_argument("Matrices are not the same size.");
        }
        SquareMatrix result(size);
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < size; ++j)
            {
                result.data[i][j] = T{};
                for (size_t k = 0; k < size; ++k)
                {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    SquareMatrix &operator*=(const SquareMatrix &other)
    {
        if (size != other.size)
        {
            throw std::invalid_argument("Matrices are not the same size.");
        }
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < size; ++j)
            {
                data[i][j] = T{};
                for (size_t k = 0; k < size; ++k)
                {
                    data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return *this;
    }

    SquareMatrix operator*(const T &scalar) const
    {
        SquareMatrix result(size);
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < size; ++j)
            {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    SquareMatrix &operator*=(const T &scalar)
    {
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < size; ++j)
            {
                data[i][j] *= scalar;
            }
        }
        return *this;
    }

    friend SquareMatrix operator*(const T &scalar, const SquareMatrix &matrix)
    {
        return matrix * scalar;
    }

    bool operator==(const SquareMatrix &other) const
    {
        if (size != other.size)
        {
            return false;
        }
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < size; ++j)
            {
                if (data[i][j] != other.data[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const SquareMatrix &other) const
    {
        return !(*this == other);
    }

    explicit operator double() const
    {
        double result{};
        for (const auto &row : data)
        {
            for (const auto &element : row)
            {
                result += static_cast<double>(element);
            }
        }
        return result;
    }

    std::vector<T> &operator[](size_t index)
    {
        return data[index];
    }

    friend std::ostream &operator<<(std::ostream &os, const SquareMatrix &matrix)
    {
        for (const auto &row : matrix.data)
        {
            for (const auto &element : row)
            {
                os << element << ' ';
            }
            os << '\n';
        }
        return os;
    }
};
