#pragma once

#include "abstract_filter.h"
#include "../color.h"
#include "../picture.h"
#include <vector>

void CopyMatrix(std::vector<std::vector<Color>>& matrix_of_pixels);

class AbstractMatrixFilter : public AbstractFilter {
public:
    void Apply(Picture& picture) override;

protected:
    virtual Color CalculateColors(const std::vector<std::vector<Color>>& matrix_of_pixels, size_t y, size_t x);

    virtual std::vector<std::vector<int>> GetMatrixOfCoeffs() = 0;
};