#pragma once

#include <array>
#include <cmath>

#include "Tuple.h"
#include "Utilities/Constants.h"

template<size_t Rows, size_t Cols>
class Matrix
{
public:
    static const Matrix<4, 4> IDENTITY;
    
    Matrix() : data{} {};
    Matrix(const std::initializer_list<std::initializer_list<float>> init) : data{} {
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

    [[nodiscard]] float Get(const size_t row, const size_t col) const
    {
        return data[row * Cols + col];
    }

    void Set(const size_t row, const size_t col, const float value)
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

    template<size_t OtherCols>
    Matrix<Rows, OtherCols> operator*(const Matrix<Cols, OtherCols>& other) const
    {
        Matrix<Rows, OtherCols> result;
        for (int row = 0; row < Rows; row++)
        {
            for (int col = 0; col < OtherCols; col++)
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

    Tuple operator*(const Tuple& tuple) const
    {
        Tuple result;
        result.x =
            Get(0, 0) * tuple.x +
            Get(0, 1) * tuple.y +
            Get(0, 2) * tuple.z +
            Get(0, 3) * tuple.w;
        
        result.y =
            Get(1, 0) * tuple.x +
            Get(1, 1) * tuple.y +
            Get(1, 2) * tuple.z +
            Get(1, 3) * tuple.w;
        
        result.z =
            Get(2, 0) * tuple.x +
            Get(2, 1) * tuple.y +
            Get(2, 2) * tuple.z +
            Get(2, 3) * tuple.w;
        
        result.w =
            Get(3, 0) * tuple.x +
            Get(3, 1) * tuple.y +
            Get(3, 2) * tuple.z +
            Get(3, 3) * tuple.w;

        return result;
    }

#pragma endregion 

	[[nodiscard]] Matrix<Rows, Cols> Transpose() const
	{
		Matrix<Rows, Cols> result;
		for (size_t row = 0; row < Rows; row++)
		{
			for (size_t col = 0; col < Cols; col++)
			{
				result.Set(col, row, Get(row, col));
			}
		}
		return result;
	}

	[[nodiscard]] float Determinant() const
	{
		if constexpr (Rows == 2 && Cols == 2)
		{
			return Get(0, 0) * Get(1, 1) - Get(0, 1) * Get(1, 0);
		}

        float det = 0;
        for (size_t col = 0; col < Cols; col++)
        {
            det += Get(0, col) * Cofactor(0, col);
        }
        return det;
	}

	[[nodiscard]] auto Submatrix(const size_t row, const size_t col) const
	{
		if constexpr (Rows >= 2 && Cols >= 2)
		{
			Matrix<Rows - 1, Cols - 1> result;
		    int resultRow = 0;
		    for (size_t i = 0; i < Rows; i++)
		    {
			    if (i == row)
			    {
				    continue;
			    }

			    int resultCol = 0;
			    for (size_t j = 0; j < Cols; j++)
			    {
				    if (j == col)
				    {
					    continue;
				    }

				    result.Set(resultRow, resultCol, Get(i, j));
				    ++resultCol;
			    }
			    ++resultRow;
		    }
		    return result;
		}
		//literally needs the "else" statement to compile correctly, can't just "return *this" on its own for some reason
        else
        {
			return *this;
		}
	}

	[[nodiscard]] float Minor(const size_t row, const size_t col) const
	{
		return Submatrix(row, col).Determinant();
	}

	[[nodiscard]] float Cofactor(const size_t row, const size_t col) const
	{
		const float minor = Minor(row, col);
		return (row + col) % 2 == 0 ? minor : -minor;
	}

	[[nodiscard]] Matrix<Rows, Cols> Inverse() const
	{
		Matrix<Rows, Cols> result;
		const float det = Determinant();
		if (det == 0.f)
		{
			throw std::runtime_error("Matrix is not invertible");
		}

		for (size_t row = 0; row < Rows; row++)
		{
			for (size_t col = 0; col < Cols; col++)
			{
				const float c = Cofactor(row, col);
				result.Set(col, row, c / det);
			}
		}

		return result;
    }

	[[nodiscard]] bool IsInvertible() const
	{
		return Determinant() != 0.f;
	}

private:
    std::array<float, Rows * Cols> data;
};

const Matrix<4, 4> Matrix<4, 4>::IDENTITY = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
};
