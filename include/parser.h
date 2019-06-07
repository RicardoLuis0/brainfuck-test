#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <vector>
#include <string>

enum operator_t{
    OPERATOR_INVALID,
    OPERATOR_MVRIGHT,
    OPERATOR_MVLEFT,
    OPERATOR_INCREMENT,
    OPERATOR_DECREMENT,
    OPERATOR_PRINT,
    OPERATOR_READ,
    OPERATOR_LBRACKET,
    OPERATOR_RBRACKET,
};

enum parse_output_type_t{
    PARSE_OUTPUT_OPERATOR,
    PARSE_OUTPUT_NUMBER,
};

struct parse_output{
    parse_output(operator_t);
    parse_output(uint32_t);
    parse_output_type_t type;
    operator_t op;
    uint32_t num;
};

std::vector<parse_output> parse(const std::string &str);

#endif // PARSER_H_INCLUDED
