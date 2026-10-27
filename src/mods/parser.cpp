#include "parser.hpp"
#include "macros.hpp"
#include "tokens.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

namespace Values {

Integer::Integer(int _content) : content(_content) {}
Symbol::Symbol(std::string &&_content) : content(_content) {}

} // namespace Values

enum ParsingState { Idle, Integer, Symbol };

const std::array<int, 10> NUMBER_CHARS{'0', '1', '2', '3', '4',
                                       '5', '6', '7', '8', '9'};

const char SPACE = ' ';
const char NEW_LINE = '\n';

void print_literals(std::vector<Values::Literal> &literals) {
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

/// no support for utf8
std::vector<Values::Literal> parse(std::string &input) {
    std::vector<Values::Literal> result;
    ParsingState state = ParsingState::Idle;

    Values::Integer cur_integer(0);
    Values::Symbol cur_symbol("");

    input.push_back('\n');

    std::string::iterator it = input.begin();

    while (it < input.end()) {
        switch (state) {

        case ParsingState::Idle:
            switch (*it) {

            case SPACE:
                // ignore spaces
                break;
            case NEW_LINE:
                break;
            default:
                // number
                if (std::find(NUMBER_CHARS.begin(), NUMBER_CHARS.end(), *it) !=
                    NUMBER_CHARS.end()) {
                    state = ParsingState::Integer;

                    it--;
                } else {
                    state = ParsingState::Symbol;

                    it--;
                }
            }

            it++;

            break;
        case ParsingState::Integer:
            if (*it == SPACE || *it == NEW_LINE) {
                result.push_back(cur_integer);
                state = ParsingState::Idle;
                cur_integer.content = 0;
                break;
            }

            if (std::find(NUMBER_CHARS.begin(), NUMBER_CHARS.end(), *it) !=
                NUMBER_CHARS.end()) {
                char num = *it - '0';
                cur_integer.content = cur_integer.content * 10 + (int)num;
            } else {
                result.push_back(cur_integer);
                state = ParsingState::Idle;
                cur_integer.content = 0;
                break;
            }

            it++;

            break;
        case ParsingState::Symbol:
            if (*it == SPACE || *it == NEW_LINE) {
                result.push_back(cur_symbol);
                state = ParsingState::Idle;
                cur_symbol.content = "";
                break;
            }

            if (std::find(NUMBER_CHARS.begin(), NUMBER_CHARS.end(), *it) !=
                NUMBER_CHARS.end()) {

                result.push_back(cur_symbol);
                state = ParsingState::Integer;
                cur_symbol.content = "";

                break;
            }

            auto possible_tokens = &tokens[cur_symbol.content.length() - 1];

            cur_symbol.content.push_back(*it);

            if (std::find(possible_tokens->begin(), possible_tokens->end(),
                          cur_symbol.content) != possible_tokens->end()) {
                // that's a valid token
                result.push_back(cur_symbol);
                state = ParsingState::Idle;
                cur_symbol.content = "";
            }

            it++;

            break;
        }
    }

    return result;
}
