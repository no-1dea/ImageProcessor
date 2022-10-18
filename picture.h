#pragma once

#include "color.h"
#include <fstream>
#include <vector>

class Picture {
public:
    Picture();

    Picture(std::ifstream& input);

    size_t GetWidth() const;
    size_t GetHeight() const;
    std::vector<std::vector<Color>> GetCopyOfPixelMatrix() const;
    Color& GetPixel(size_t row, size_t column);

    void ChangeWidth(size_t new_width);
    void ChangeHeight(size_t new_height);

    void Save(std::ofstream& output);

private:
    size_t height_;
    size_t width_;
    std::vector<std::vector<Color>> data_;
};
