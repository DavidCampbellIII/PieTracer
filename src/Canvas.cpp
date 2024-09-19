#include "Canvas.h"
#include "Color.h"

Canvas::Canvas(const int _width, const int _height) :
    width(_width), height(_height),
    pixels(_height, std::vector<Color>(_width, Color(0, 0, 0)))
{}

Color Canvas::PixelAt(const int x, const int y) const
{
    return pixels[y][x];
}

void Canvas::WritePixel(const int x, const int y, const Color& color)
{
    if(x < 0 || x >= width || y < 0 || y >= height)
    {
        return;
    }
    pixels[y][x] = color;
}

void Canvas::Clear(const Color& color)
{
    for(std::vector<Color>& row : pixels)
    {
        for(int i = 0; i < width; i++)
        {
            row[i] = color;
        }
    }
}

std::string Canvas::ToPPM() const
{
    const std::string header = "P3\n" + std::to_string(width) + " " + std::to_string(height) + "\n255\n";
    std::string ppm = header;
    for(const std::vector<Color>& row : pixels)
    {
        int lineLength = 0;
        for(const Color& color : row)
        {
            const std::string colorString = color.ToString();
            //add 1 to account for the space and 2 for the newline for total of 3
            if(lineLength + colorString.length() + 3 >= 70)
            {
                ppm += "\n";
                lineLength = 0;
            }
            //don't need to add a space if it's the first color in the line
            else if(lineLength > 0)
            {
                ppm += " ";
                lineLength++;
            }
            ppm += colorString;
            lineLength += colorString.length();
        }
        ppm += "\n";
    }
    return ppm + "\n";
}
