#include "parser.h"

#include <map>

static std::map<char,operator_t> parse_table{
    {'>',OPERATOR_MVRIGHT},
    {'<',OPERATOR_MVLEFT},
    {'+',OPERATOR_INCREMENT},
    {'-',OPERATOR_DECREMENT},
    {'.',OPERATOR_PRINT},
    {',',OPERATOR_READ},
    {'[',OPERATOR_LBRACKET},
    {']',OPERATOR_RBRACKET},
};

std::vector<operator_t> parse(const std::string &str){
    std::vector<operator_t> o;
    for(char c:str){
        if(parse_table.find(c)!=parse_table.end()){
            o.push_back(parse_table[c]);
        }
    }
    return  o;
}
