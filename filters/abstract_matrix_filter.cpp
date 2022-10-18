#include "abstract_matrix_filter.h"
#include <algorithm>

namespace {
std::vector<std::vector<Color>> CopyMatrix(Picture& picture) {
    size_t height = picture.GetHeight();
    size_t width = picture.GetWidth();
    std::vector<std::vector<Color>> matrix_of_pixels(height + 2, std::vector<Color>(width + 2));

    matrix_of_pixels[0][0] = picture.GetPixel(0, 0);
    matrix_of_pixels[height + 1][width + 1] = picture.GetPixel(height - 1, width - 1);
    matrix_of_pixels[height + 1][0] = picture.GetPixel(height - 1, 0);
    matrix_of_pixels[0][width + 1] = picture.GetPixel(0, width - 1);

    for (size_t i = 1; i < width + 1; ++i) {
        matrix_of_pixels[0][i] = picture.GetPixel(0, i - 1);
        matrix_of_pixels[height + 1][i] = picture.GetPixel(height - 1, i - 1);
    }

    for (size_t i = 1; i < height + 1; ++i) {
        matrix_of_pixels[i][0] = picture.GetPixel(i - 1, 0);
        matrix_of_pixels[i][width + 1] = picture.GetPixel(i - 1, width - 1);
    }

    for (size_t i = 1; i < height + 1; ++i) {
        for (size_t j = 1; j < width + 1; ++j) {
            matrix_of_pixels[i][j] = picture.GetPixel(i - 1, j - 1);
        }
    }
    return matrix_of_pixels;
}
}  // namespace

void AbstractMatrixFilter::Apply(Picture& picture) {
    auto matrix_of_pixels = CopyMatrix(picture);

    for (size_t y = 0; y < picture.GetHeight(); ++y) {
        for (size_t x = 0; x < picture.GetWidth(); ++x) {
            picture.GetPixel(y, x) = CalculateColors(matrix_of_pixels, y, x);
        }
    }
}

Color AbstractMatrixFilter::CalculateColors(const std::vector<std::vector<Color>>& matrix_of_pixels, size_t y,
                                            size_t x) {
    int result_red = 0;
    int result_green = 0;
    int result_blue = 0;
    auto matrix_of_coeffs = GetMatrixOfCoeffs();

    for (int sh_y = -1; sh_y <= 1; ++sh_y) {
        for (int sh_x = -1; sh_x <= 1; ++sh_x) {
            result_red += matrix_of_coeffs[sh_y + 1][sh_x + 1] * matrix_of_pixels[y + 1 + sh_y][x + 1 + sh_x].red;
            result_green += matrix_of_coeffs[sh_y + 1][sh_x + 1] * matrix_of_pixels[y + 1 + sh_y][x + 1 + sh_x].green;
            result_blue += matrix_of_coeffs[sh_y + 1][sh_x + 1] * matrix_of_pixels[y + 1 + sh_y][x + 1 + sh_x].blue;
        }
    }
    return {static_cast<uint8_t>(std::clamp(result_red, 0, 255)),
            static_cast<uint8_t>(std::clamp(result_green, 0, 255)),
            static_cast<uint8_t>(std::clamp(result_blue, 0, 255))};
}
