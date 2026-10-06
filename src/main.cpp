#include "mods/parser.hpp"
#include <fstream>
#include <string>

int main() {
    std::ifstream input_file("main.mlts");

    std::string input;
    std::string line;

    while (std::getline(input_file, line)) {
        input += line;
    }

    input_file.close();

    return 0;
}
