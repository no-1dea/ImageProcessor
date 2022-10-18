#pragma once

#include "../filters/abstract_filter.h"
#include <memory>
#include <string>

class Parser {
public:
    Parser(int argc, char** argv);

    std::string GetInputFile();
    std::string GetOutPutFile();

    std::vector<std::shared_ptr<AbstractFilter>> GetFilters();

private:
    std::string path_of_input_file_;
    std::string path_of_output_file_;
    std::vector<std::shared_ptr<AbstractFilter>> filters_;
};
