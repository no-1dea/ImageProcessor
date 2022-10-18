#include "controller.h"
#include "parser/parser.h"

int main(int argc, char** argv) {
    Parser parser(argc, argv);
    Controller controller(parser.GetInputFile(), parser.GetOutPutFile());
    controller.ApplyFilters(parser.GetFilters());
}
