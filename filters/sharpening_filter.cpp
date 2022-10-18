#include "sharpening_filter.h"

std::vector<std::vector<int>> SharpeningFilter::GetMatrixOfCoeffs() {
    static const std::vector<std::vector<int>> matrix_of_coeffs = {{0, -1, 0},
                                                                   {-1, 5, -1},
                                                                   {0, -1, 0}};
    return matrix_of_coeffs;
}
