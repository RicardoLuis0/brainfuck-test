#include "parser.h"

#include <map>
#include <stack>

parse_output::parse_output(operator_t o):type(PARSE_OUTPUT_OPERATOR),op(o),num(0){
}
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

std::vector<parse_output> parse(const std::string &str){
    std::vector<parse_output> o;
    std::stack<uint32_t> open_brackets;
    for(char c:str){
        if(parse_table.find(c)!=parse_table.end()){
            operator_t op=parse_table[c];
            o.push_back(op);
            if(op==OPERATOR_LBRACKET){
                open_brackets.push(o.size()-1);
            }else if(op==OPERATOR_RBRACKET){
                o[open_brackets.top()].num=o.size()-1;
                open_brackets.pop();
            }
        }
    }
    return  o;
}
