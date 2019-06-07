#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <vector>
#include <map>
#include <cstdint>
#include <stack>

long find_file_size(FILE * f){
    fseek(f,0,SEEK_END);
    long o=ftell(f);
    fseek(f,0,SEEK_SET);
    return o;
}

std::string readfile(std::string filename){
    std::cout<<"reading file "<<filename<<"\n";
    FILE * f=fopen(filename.c_str(),"r");
    if(!f){
        throw std::runtime_error("could not open file");
    }
    std::string out;
    out.reserve(find_file_size(f));
    for(char c;(c=fgetc(f))!=EOF;)out+=c;
    fclose(f);
    return out;
}

enum operator_t{
    OPERATOR_MVRIGHT,
    OPERATOR_MVLEFT,
    OPERATOR_INCREMENT,
    OPERATOR_SUBTRACT,
    OPERATOR_PRINT,
    OPERATOR_READ,
    OPERATOR_LBRACKET,
    OPERATOR_RBRACKET,
};

static std::map<char,operator_t> parse_table{
    {'>',OPERATOR_MVRIGHT},
    {'<',OPERATOR_MVLEFT},
    {'+',OPERATOR_INCREMENT},
    {'-',OPERATOR_SUBTRACT},
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

int main(int argc,char ** argv){
    if(argc<2){
        std::cout<<"Missing File Argument, usage: program \"file\"\n";
        return 1;
    }
    try{
        std::vector<operator_t> program=parse(readfile(argv[1]));
        std::stack<uint32_t> stack;
        std::map<int32_t,uint8_t> tape;
        bool skip=false;
        uint32_t skip_counter=0;
        uint32_t pc=0;//program counter
        int32_t ap=0;//address counter, can be negative
        for(pc=0;pc<program.size();pc++){
            if(skip){
                if(program[pc]==OPERATOR_LBRACKET){
                    skip_counter++;
                }else if(program[pc]==OPERATOR_RBRACKET){
                    if(skip_counter>0){
                        skip_counter--;
                    }else{
                        skip=false;
                    }
                }
                continue;
            }
            switch(program[pc]){
            case OPERATOR_MVRIGHT:
                ap++;
                break;
            case OPERATOR_MVLEFT:
                ap--;
                break;
            case OPERATOR_INCREMENT:
                tape[ap]++;
                break;
            case OPERATOR_SUBTRACT:
                tape[ap]--;
                break;
            case OPERATOR_PRINT:
                std::cout<<char(tape[ap]);
                break;
            case OPERATOR_READ:
                //TODO
                break;
            case OPERATOR_LBRACKET:
                if(tape[ap]==0){//skip block if is zero
                    skip=true;
                    skip_counter=0;
                }else{
                    stack.push(pc);
                }
                break;
            case OPERATOR_RBRACKET:
                if(tape[ap]!=0){
                    pc=stack.top();
                }else{
                    stack.pop();
                }
                break;
            }
        }
    }catch(std::exception &e){
        std::cout<<"failed with exception:\n  "<<e.what()<<"\n";
        return 1;
    }
}
