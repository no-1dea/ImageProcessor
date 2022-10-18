#pragma once

#include "abstract_matrix_filter.h"
#include <vector>

class EdgeDetectionFilter : public AbstractMatrixFilter {
public:
    explicit EdgeDetectionFilter(int threshold);

    void Apply(Picture& picture) override;

protected:
    int threshold_ = 255;

    std::vector<std::vector<int>> GetMatrixOfCoeffs() override;
};
