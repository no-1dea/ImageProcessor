#include "../color.h"
#include "edge_detection_filter.h"
#include "gray_scale_filter.h"
#include <algorithm>

namespace {
Color ClampColor(Color& value, int low, int high) {
    if (value.red > high) {
        return {255, 255, 255};
    } else if (value.red < low) {
        return {0, 0, 0};
    }
    return value;
}
}  // namespace

EdgeDetectionFilter::EdgeDetectionFilter(int threshold) : threshold_(std::min(std::max(0, threshold), 255)) {
}

void EdgeDetectionFilter::Apply(Picture& picture) {
    GrayScaleFilter gray_scale_filter;
    gray_scale_filter.Apply(picture);
    AbstractMatrixFilter::Apply(picture);

    for (size_t y = 0; y < picture.GetHeight(); ++y) {
        for (size_t x = 0; x < picture.GetWidth(); ++x) {
            picture.GetPixel(y, x) = ClampColor(picture.GetPixel(y, x), 0, threshold_);
        }
    }
}

std::vector<std::vector<int>> EdgeDetectionFilter::GetMatrixOfCoeffs() {
    static const std::vector<std::vector<int>> matrix_of_coeffs = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    return matrix_of_coeffs;
}
