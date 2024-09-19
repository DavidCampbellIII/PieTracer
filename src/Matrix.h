#pragma once

#include <array>
#include <cmath>

#include "Utilities/Constants.h"

template<size_t Rows, size_t Cols>
class Matrix
{
public:
    Matrix() {}
    Matrix(const std::initializer_list<std::initializer_list<float>> init) {
        size_t row = 0;
        for (const auto& row_list : init) {
            size_t col = 0;
            for (const float& value : row_list) {
                if (row < Rows && col < Cols) {
                    data[row * Cols + col] = value;
                }
                ++col;
            }
            ++row;
        }
    }

    float Get(const int row, const int col) const
    {
        return data[row * Cols + col];
    }

    void Set(const int row, const int col, const float value)
    {
        data[row * Cols + col] = value;
    }

#pragma region Equality

    bool operator==(const Matrix& other) const
    {
        for (int i = 0; i < Rows * Cols; i++)
        {
            if (std::fabsf(data[i] - other.data[i]) >= EPSILON)
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Matrix& other) const
    {
        return !(*this == other);
    }

#pragma endregion

#pragma region Multiplication

    Matrix<Rows, Cols> operator*(const Matrix<Rows, Cols>& other) const
    {
        Matrix<Rows, Cols> result;
        for (int row = 0; row < Rows; row++)
        {
            for (int col = 0; col < Cols; col++)
            {
                float sum = 0;
                for (int i = 0; i < Cols; i++)
                {
                    sum += Get(row, i) * other.Get(i, col);
                }
                result.Set(row, col, sum);
            }
        }
        return result;
    }

#pragma endregion 

private:
    std::array<float, Rows * Cols> data;
};
