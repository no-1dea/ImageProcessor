#include "controller.h"

Controller::Controller(const std::string& input, const std::string& output) {
    input_ = std::ifstream(input, std::ios::binary);
    output_ = std::ofstream(output, std::ios::binary);
    if (!(input_ && output_)) {
        throw std::exception();
    }
    picture_ = Picture(input_);
}

void Controller::ApplyFilters(const std::vector<std::shared_ptr<AbstractFilter>>& filters) {
    for (const auto& filter : filters) {
        filter->Apply(picture_);
    }
    picture_.Save(output_);
}
