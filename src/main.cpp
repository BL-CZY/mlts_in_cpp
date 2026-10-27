// #include "mods/parser.hpp"
// #include <fstream>
#include "mods/parser.hpp"
#include <cstddef>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

int main() {
    // std::ifstream input_file("main.mlts");
    //
    // std::string input;
    // std::string line;
    //
    // while (std::getline(input_file, line)) {
    //     input += line;
    // }
    //
    // input_file.close();

    while (true) {
        std::cout << "odyc++ > ";
        std::string input;
        std::getline(std::cin, input);

        std::vector<Values::Literal> literals = parse(input);

        for (size_t i = 0; i < literals.size(); ++i) {
            std::visit(overloaded{
                           [](Values::Integer &integer) {
                               std::cout << "Number: " << integer.content
                                         << std::endl;
                           },
                           [](Values::Symbol &symbol) {
                               std::cout << "Symbol: " << symbol.content
                                         << std::endl;
                           },
                       },
                       literals[i]);
        }
    }

    return 0;
}
