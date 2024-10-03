#pragma once

#include <string>
#include <vector>

struct Color;

class Canvas
{
public:
    [[nodiscard]] int GetWidth() const { return width; }
    [[nodiscard]] int GetHeight() const { return height; }
    
    Canvas(const int _width, const int _height);
    
    [[nodiscard]] Color PixelAt(const int x, const int y) const;
    void WritePixel(const int x, const int y, const Color& color);

    void Clear(const Color& color);

    [[nodiscard]] std::string ToPPM() const;
    
private:
    int width;
    int height;
    std::vector<std::vector<Color>> pixels;
};
