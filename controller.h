#pragma once

#include "filters/list_of_filters.h"
#include "picture.h"
#include <fstream>
#include <memory>
#include <string>
#include <vector>

class Controller {
public:
    Controller(const std::string& input, const std::string& output);

    void ApplyFilters(const std::vector<std::shared_ptr<AbstractFilter>>& filters);

private:
    std::ifstream input_;
    std::ofstream output_;
    Picture picture_;
};
