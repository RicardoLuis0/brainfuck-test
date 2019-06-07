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
        std::vector<uint8_t> tape;//positive tape, from 0 to infinity
        std::vector<uint8_t> tape2;//negative tape, from -1 to infinity
        const uint32_t tape_increment=1024;
        tape.resize(tape_increment,0);
        tape2.resize(tape_increment,0);
        uint32_t pc=0;//program counter
        int32_t ap=0;//address counter, can be negative
        auto get=[&]()->uint8_t&{
            return (ap<0?tape2[(-ap)-1]:tape[ap]);
        };
        for(pc=0;pc<program.size();pc++){
            if(ap>=0&&uint32_t(ap+1)>tape.size()){//if tape is too small, resize it
                tape.resize(tape.size()+tape_increment,0);
            }
            if(ap<0&&uint32_t(-ap)>tape2.size()){//if tape is too small, resize it
                tape2.resize(tape2.size()+tape_increment,0);
            }
            switch(program[pc]){
            case OPERATOR_MVRIGHT:
                ap++;
                break;
            case OPERATOR_MVLEFT:
                ap--;
                break;
            case OPERATOR_INCREMENT:
                get()++;
                break;
            case OPERATOR_SUBTRACT:
                get()--;
                break;
            case OPERATOR_PRINT:
                std::cout<<char(get());
                break;
            case OPERATOR_READ:
                //TODO
                break;
            case OPERATOR_LBRACKET:
                stack.push(pc);
                break;
            case OPERATOR_RBRACKET:
                if(get()>0){
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
