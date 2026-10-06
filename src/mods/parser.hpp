#pragma once

#include <string>
#include <variant>
#include <vector>

namespace Values {

class Integer {
  public:
    int content;
    Integer(int _content);
};
class Symbol {
  public:
    std::string content;
    Symbol(std::string &&_content);
};

using Literal = std::variant<Integer, Symbol>;

}; // namespace Values

std::vector<Values::Literal> parse(std::string &input);
