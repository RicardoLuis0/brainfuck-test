#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <vector>
#include <string>

enum operator_t{
    OPERATOR_MVRIGHT,
    OPERATOR_MVLEFT,
    OPERATOR_INCREMENT,
    OPERATOR_DECREMENT,
    OPERATOR_PRINT,
    OPERATOR_READ,
    OPERATOR_LBRACKET,
    OPERATOR_RBRACKET,
};

std::vector<operator_t> parse(const std::string &str);

#endif // PARSER_H_INCLUDED
