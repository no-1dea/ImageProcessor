#include "../filters/list_of_filters.h"
#include "parser.h"
#include <exception>
#include <functional>
#include <unordered_map>

namespace {
std::shared_ptr<AbstractFilter> CreateCrop(int* position, char** arguments) {
    size_t witdh = std::stoul(arguments[++(*position)]);
    size_t height = std::stoul(arguments[++(*position)]);
    return std::make_shared<CropFilter>(witdh, height);
}

std::shared_ptr<AbstractFilter> CreateEdgeDetectionFilter(int* position, char** arguments) {
    double threshold = std::stod(arguments[++(*position)]);
    return std::make_shared<EdgeDetectionFilter>(threshold * 255);
}

std::shared_ptr<AbstractFilter> CreateGaussianBlur(int* position, char** arguments) {
    double sigma = std::stod(arguments[++(*position)]);
    return std::make_shared<GaussianBlurFilter>(sigma);
}

std::shared_ptr<AbstractFilter> CreateGrayScaleFilter(int* position, char** arguments) {
    return std::make_shared<GrayScaleFilter>();
}

std::shared_ptr<AbstractFilter> CreateNegativeFilter(int* position, char** arguments) {
    return std::make_shared<NegativeFilter>();
}

std::shared_ptr<AbstractFilter> CreatePixelizationEffectFilter(int* position, char** arguments) {
    size_t diameter = std::stoul(arguments[++(*position)]);
    return std::make_shared<PixelizationEffectFilter>(diameter);
}

std::shared_ptr<AbstractFilter> CreateSharpeningFilter(int* position, char** arguments) {
    return std::make_shared<SharpeningFilter>();
}

std::unordered_map<std::string, std::function<std::shared_ptr<AbstractFilter>(int*, char**)>> GetListOfCreatorFuncs() {
    std::unordered_map<std::string, std::function<std::shared_ptr<AbstractFilter>(int*, char**)>> list;
    list["-crop"] = CreateCrop;
    list["-edge"] = CreateEdgeDetectionFilter;
    list["-blur"] = CreateGaussianBlur;
    list["-gs"] = CreateGrayScaleFilter;
    list["-neg"] = CreateNegativeFilter;
    list["-px"] = CreatePixelizationEffectFilter;
    list["-sharp"] = CreateSharpeningFilter;
    return list;
}
};  // namespace

Parser::Parser(int argc, char** argv) : path_of_input_file_(argv[1]), path_of_output_file_(argv[2]) {
    filters_ = {};
    static auto list_of_filters = GetListOfCreatorFuncs();

    for (int i = 3; i < argc; ++i) {
        if (argv[i][0] == '-' && list_of_filters.contains(argv[i])) {
            filters_.push_back(list_of_filters[argv[i]](&i, argv));
        } else {
            throw std::exception();
        }
    }
}

std::string Parser::GetInputFile() {
    return path_of_input_file_;
}

std::string Parser::GetOutPutFile() {
    return path_of_output_file_;
}

std::vector<std::shared_ptr<AbstractFilter>> Parser::GetFilters() {
    return filters_;
}
