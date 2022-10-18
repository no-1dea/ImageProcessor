#include "pixelization_effect_filter.h"
#include <algorithm>
#include <cstdint>

namespace {
Color CalculateAverageColor(const std::vector<std::vector<Color>>& matrix_of_pixels, size_t y, size_t x,
                            size_t diameter) {
    int sum_red = 0;
    int sum_green = 0;
    int sum_blue = 0;
    int count_of_pixels = 0;

    for (size_t i = y; i < std::min(matrix_of_pixels.size(), y + diameter); ++i) {
        for (size_t j = x; j < std::min(matrix_of_pixels[0].size(), x + diameter); ++j) {
            sum_red += matrix_of_pixels[i][j].red;
            sum_green += matrix_of_pixels[i][j].green;
            sum_blue += matrix_of_pixels[i][j].blue;
            count_of_pixels += 1;
        }
    }

    return {static_cast<uint8_t>(sum_red / count_of_pixels), static_cast<uint8_t>(sum_green / count_of_pixels),
            static_cast<uint8_t>(sum_blue / count_of_pixels)};
}

void PixelizationSquare(Picture& picture, const std::vector<std::vector<Color>>& matrix_of_pixels, size_t y, size_t x,
                        size_t diameter) {
    Color new_color = CalculateAverageColor(matrix_of_pixels, y, x, diameter);
    for (size_t i = y; i < std::min(picture.GetHeight(), y + diameter); ++i) {
        for (size_t j = x; j < std::min(picture.GetWidth(), x + diameter); ++j) {
            picture.GetPixel(i, j) = new_color;
        }
    }
}
}  // namespace

PixelizationEffectFilter::PixelizationEffectFilter(size_t diameter) : diameter_(std::max<size_t>(1, diameter)) {
}

void PixelizationEffectFilter::Apply(Picture& picture) {
    size_t height = picture.GetHeight();
    size_t width = picture.GetWidth();
    std::vector<std::vector<Color>> matrix_of_pixels = picture.GetCopyOfPixelMatrix();

    for (size_t y = 0; y < height; y += diameter_) {
        for (size_t x = 0; x < width; x += diameter_) {
            PixelizationSquare(picture, matrix_of_pixels, y, x, diameter_);
        }
    }
}
