#include "gaussian_blur.h"
#include <cmath>

namespace {
using Coordinate = std::pair<const size_t, const size_t>;

double CalculateGaussConstant(Coordinate p1, Coordinate p2, const double sigma) {
    double const_coeff = 1.0 / std::sqrt(2 * M_PI * sigma * sigma);
    double variable_coeff =
        std::pow(M_E, (std::pow(std::abs(static_cast<int>(p1.first) - static_cast<int>(p2.first)), 2) +
                       std::pow(std::abs(static_cast<int>(p1.second) - static_cast<int>(p2.second)), 2)) /
                          (-2 * sigma * sigma));
    return const_coeff * variable_coeff;
}
}  // namespace

GaussianBlurFilter::GaussianBlurFilter(double sigma) : sigma_(sigma) {
}

void GaussianBlurFilter::HorizontalSum(Picture& picture, std::vector<std::vector<Color>>& matrix_of_pixels, size_t i,
                                       size_t j) {
    double result_red = 0;
    double result_green = 0;
    double result_blue = 0;
    for (size_t new_j = 0; new_j < picture.GetWidth(); ++new_j) {
        if (std::abs(static_cast<int>(j) - static_cast<int>(new_j)) <= static_cast<int>(3 * sigma_)) {
            double gauss_const = CalculateGaussConstant({i, j}, {i, new_j}, sigma_);
            result_red += gauss_const * matrix_of_pixels[i][new_j].red;
            result_green += gauss_const * matrix_of_pixels[i][new_j].green;
            result_blue += gauss_const * matrix_of_pixels[i][new_j].blue;
        }
    }

    picture.GetPixel(i, j) = {static_cast<uint8_t>(std::clamp(result_red, 0.0, 255.0)),
                              static_cast<uint8_t>(std::clamp(result_green, 0.0, 255.0)),
                              static_cast<uint8_t>(std::clamp(result_blue, 0.0, 255.0))};
}

void GaussianBlurFilter::VerticalSum(Picture& picture, std::vector<std::vector<Color>>& matrix_of_pixels, size_t i,
                                     size_t j) {
    double result_red = 0;
    double result_green = 0;
    double result_blue = 0;
    for (size_t new_i = 0; new_i < picture.GetHeight(); ++new_i) {
        if (std::abs(static_cast<int>(i) - static_cast<int>(new_i)) <= static_cast<int>(3 * sigma_)) {
            double gauss_const = CalculateGaussConstant({i, j}, {new_i, j}, sigma_);
            result_red += gauss_const * matrix_of_pixels[new_i][j].red;
            result_green += gauss_const * matrix_of_pixels[new_i][j].green;
            result_blue += gauss_const * matrix_of_pixels[new_i][j].blue;
        }
    }

    picture.GetPixel(i, j) = {static_cast<uint8_t>(std::clamp(result_red, 0.0, 255.0)),
                              static_cast<uint8_t>(std::clamp(result_green, 0.0, 255.0)),
                              static_cast<uint8_t>(std::clamp(result_blue, 0.0, 255.0))};
}

void GaussianBlurFilter::Apply(Picture& picture) {
    size_t height = picture.GetHeight();
    size_t width = picture.GetWidth();

    std::vector<std::vector<Color>> matrix_of_pixels = picture.GetCopyOfPixelMatrix();
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            HorizontalSum(picture, matrix_of_pixels, i, j);
        }
    }

    matrix_of_pixels = picture.GetCopyOfPixelMatrix();
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            VerticalSum(picture, matrix_of_pixels, i, j);
        }
    }
}
