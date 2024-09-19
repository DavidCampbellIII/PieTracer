#pragma once

#include <cmath>
#include <cfloat>
#include <algorithm>

struct Color
{
public:
    float r;
    float g;
    float b;

    Color() : r(0), g(0), b(0) {}
    Color(const float _r, const float _g, const float _b) :
        r(_r), g(_g), b(_b) {}

#pragma region Equality

    bool operator==(const Color& other) const
    {
        return std::fabsf(r - other.r) < FLT_EPSILON &&
            std::fabsf(g - other.g) < FLT_EPSILON &&
            std::fabsf(b - other.b) < FLT_EPSILON;
    }

    bool operator!=(const Color& other) const
    {
        return !(*this == other);
    }

#pragma endregion 

#pragma region Addition

    Color operator+(const Color& other) const
    {
        return Color(
            r + other.r,
            g + other.g,
            b + other.b);
    }

    Color& operator+=(const Color& other)
    {
        r += other.r;
        b += other.b;
        g += other.g;
        return *this;
    }

#pragma endregion

#pragma region Subtraction

    Color operator-(const Color& other) const
    {
        return Color(
            r - other.r,
            g - other.g,
            b - other.b);
    }

    Color& operator-=(const Color& other)
    {
        r -= other.r;
        g -= other.g;
        b -= other.b;
        return *this;
    }

#pragma endregion

#pragma region Multiplication

    Color operator*(const float scalar) const
    {
        return Color(
            r * scalar,
            g * scalar,
            b * scalar);
    }

    Color& operator*=(const float scalar)
    {
        r *= scalar;
        g *= scalar;
        b *= scalar;
        return *this;
    }

    Color operator*(const Color& other) const
    {
        return Color(
            r * other.r,
            g * other.g,
            b * other.b);
    }

    Color& operator*=(const Color& other)
    {
        r *= other.r;
        g *= other.g;
        b *= other.b;
        return *this;
    }

#pragma endregion

    std::string ToString() const
    {
        const int rInt = static_cast<int>(std::round(std::clamp(r, 0.f, 1.f) * 255));
        const int gInt = static_cast<int>(std::round(std::clamp(g, 0.f, 1.f) * 255));
        const int bInt = static_cast<int>(std::round(std::clamp(b, 0.f, 1.f) * 255));
        return std::to_string(rInt) + " " + std::to_string(gInt) + " " + std::to_string(bInt);
    }
};
