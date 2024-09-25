#pragma once

#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>

#include "Utilities/Constants.h"
#include "Utilities/Utilities.h"

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
        return std::fabsf(r - other.r) < EPSILON &&
            std::fabsf(g - other.g) < EPSILON &&
            std::fabsf(b - other.b) < EPSILON;
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

    friend std::ostream& operator<<(std::ostream& os, const Color& color) {
        return os << "Color(" << color.r << ", " << color.g << ", " << color.b << ")";
    }

    [[nodiscard]] std::string ToString() const
    {
        const int rInt = static_cast<int>(std::round(Utilities::Clamp01(r) * 255));
        const int gInt = static_cast<int>(std::round(Utilities::Clamp01(g) * 255));
        const int bInt = static_cast<int>(std::round(Utilities::Clamp01(b) * 255));
        return std::to_string(rInt) + " " + std::to_string(gInt) + " " + std::to_string(bInt);
    }
};
