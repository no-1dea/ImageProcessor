#pragma once

#include "abstract_matrix_filter.h"
#include <vector>

class SharpeningFilter : public AbstractMatrixFilter {
protected:
    std::vector<std::vector<int>> GetMatrixOfCoeffs() override;
};
