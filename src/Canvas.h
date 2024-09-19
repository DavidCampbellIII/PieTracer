#pragma once
#include <string>
#include <vector>

struct Color;

class Canvas
{
public:
    int Width() const { return width; }
    int Height() const { return height; }
    
    Canvas(const int _width, const int _height);
    
    Color PixelAt(const int x, const int y) const;
    void WritePixel(const int x, const int y, const Color& color);

    void Clear(const Color& color);

    std::string ToPPM() const;
    
private:
    int width;
    int height;
    std::vector<std::vector<Color>> pixels;
};
