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

void print_literals(std::vector<Literal> &literals);

}; // namespace Values

template <class... Ts> struct overloaded : Ts... {
    using Ts::operator()...;
};
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

std::vector<Values::Literal> parse(std::string &input);
