#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class SquareMatrix
{
private:
    T **data;
    size_t size;

    class InnerMatrix
    {
    private:
        T *data;
        size_t size;

    public:
        InnerMatrix(T *data, size_t size) : data(data), size(size) {}

        T &operator[](size_t i) const
        {
            return data[i];
        }
    };

public:
    InnerMatrix operator[](size_t i) const
    {
        return InnerMatrix(data[i], size);
    }

    size_t get_size() const
    {
        return size;
    }

    SquareMatrix(size_t size) : size(size)
    {
        if (size == 0)
            return;

        data = new T *[size];
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = new T[size];
        }
    }

    SquareMatrix() : SquareMatrix(0) {}

    explicit SquareMatrix(T *diagonal, size_t size) : SquareMatrix(size)
    {
        for (size_t i = 0; i < size; ++i)
        {
            data[i][i] = diagonal[i];
        }
    }

    SquareMatrix(T **matrix, size_t size) : SquareMatrix(size)
    {
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < size; ++j)
            {
                data[i][j] = matrix[i][j];
            }
        }
    }

    explicit SquareMatrix(size_t size, T value) : SquareMatrix(size)
    {
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < size; ++j)
            {
                this->data[i][j] = value;
            }
        }
    }

    SquareMatrix(const SquareMatrix &other)
    {
        size = other.size;
        data = new T *[size];
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = new T[size];
            for (size_t j = 0; j < size; ++j)
            {
                data[i][j] = other.data[i][j];
            }
        }
    }

    SquareMatrix(SquareMatrix &&other) noexcept
        : size(std::move(other.size)), data(std::move(other.data))
    {
        other.data = nullptr;
        other.size = 0;
    }

    SquareMatrix submatrix(size_t row, size_t col) const
    {
        SquareMatrix sub(size - 1);
        for (size_t i = 0, sub_i = 0; i < size; ++i)
        {
            if (i == row)
                continue;
            for (size_t j = 0, sub_j = 0; j < size; ++j)
            {
                if (j == col)
                    continue;
                sub.data[sub_i][sub_j] = data[i][j];
                sub_j++;
            }
            sub_i++;
        }
        return sub;
    }

    T determinant() const
    {
        if (size == 0)
            return 0;
        if (size == 1)
            return data[0][0];
        if (size == 2)
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];

        T det = 0;
        for (size_t i = 0; i < size; ++i)
        {

            SquareMatrix sub = submatrix(0, i);

            T sub_det = sub.determinant();

            det += (i % 2 == 0 ? 1 : -1) * data[0][i] * sub_det;
        }
        return det;
    }

    SquareMatrix &operator=(const SquareMatrix &other)
    {
        if (this != &other)
        {
            size = other.size;
            data = new T *[size];
            for (size_t i = 0; i < size; ++i)
            {
                data[i] = new T[size];
                for (size_t j = 0; j < size; ++j)
                {
                    data[i][j] = other.data[i][j];
                }
            }
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

    ~SquareMatrix()
    {
        if (size == 0)
            return;

        for (size_t i = 0; i < size; ++i)
        {
            delete[] data[i];
        }
        delete[] data;
    }

    // why we return by value?
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

    // why by reference?
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
        return determinant();
    }

    friend std::ostream &operator<<(std::ostream &os, const SquareMatrix &matrix)
    {
        for (size_t i = 0; i < matrix.size; ++i)
        {
            for (size_t j = 0; j < matrix.size; ++j)
            {
                os << matrix.data[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }
};
