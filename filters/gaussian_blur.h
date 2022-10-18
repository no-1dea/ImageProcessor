#pragma once

#include "abstract_filter.h"
#include "../color.h"
#include <vector>

class GaussianBlurFilter : public AbstractFilter {
public:
    explicit GaussianBlurFilter(double sigma);

    void Apply(Picture& picture) override;

protected:
    void HorizontalSum(Picture& picture, std::vector<std::vector<Color>>& matrix_of_pixels, size_t i, size_t j);
    void VerticalSum(Picture& picture, std::vector<std::vector<Color>>& matrix_of_pixels, size_t i, size_t j);

    double sigma_;
};
