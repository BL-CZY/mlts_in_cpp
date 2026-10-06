#include "parser.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

enum ParsingState { Idle, Integer, Symbol };

const std::array<int, 10> NUMBER_CHARS{'0', '1', '2', '3', '4',
                                       '5', '6', '7', '8', '9'};

const char SPACE = ' ';
const char NEW_LINE = '\n';

/// no support for utf8
std::vector<Values::Literal> parse(std::string &input) {
    std::vector<Values::Literal> result;
    ParsingState state = ParsingState::Idle;

    Values::Integer cur_integer(0);
    Values::Symbol cur_symbol("");

    for (auto it = input.begin(); it < input.end(); ++it) {
        switch (state) {
        case ParsingState::Idle:
            switch (*it) {
            case SPACE:
                // ignore spaces
                break;
            default:
                // number
                if (std::find(NUMBER_CHARS.begin(), NUMBER_CHARS.end(), *it) !=
                    NUMBER_CHARS.end()) {
                    state = ParsingState::Integer;
                    cur_integer = Values::Integer(0);
                } else {
                    state = ParsingState::Symbol;
                    cur_symbol = Values::Symbol("");
                }
            }

            break;
        case ParsingState::Integer:
            if (*it == SPACE || *it == NEW_LINE) {
                result.push_back(cur_integer);
                state = ParsingState::Idle;
                break;
            }

            if (std::find(NUMBER_CHARS.begin(), NUMBER_CHARS.end(), *it) !=
                NUMBER_CHARS.end()) {
                char num = *it - '0';
                cur_integer.content = cur_integer.content * 10 + (int)num;
            } else {
                // TODO: do this
                std::cerr << "Some number error" << std::endl;
            }

            break;
        case ParsingState::Symbol:
            if (*it == SPACE || *it == NEW_LINE) {
                result.push_back(cur_symbol);
                state = ParsingState::Idle;
                break;
            }

            cur_symbol.content.push_back(*it);

            break;
        }
    }

    return result;
}
