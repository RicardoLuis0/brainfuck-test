#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <cstdint>
#include <stack>

#include "readfile.h"
#include "parser.h"

int main(int argc,char ** argv){
    if(argc<2){
        std::cout<<"Missing File Argument, usage: program \"file\"\n";
        return 1;
    }
    try{
        std::vector<operator_t> program=parse(readfile(argv[1]));//parse the program at argv[1]
        std::stack<uint32_t> stack;//stack, where the locations are stored during loops
        std::map<int32_t,uint8_t> tape;//tape, where the data is stored
        bool skip=false;//wether to skip block
        uint32_t skip_depth=0;//depth of current skip
        uint32_t pc=0;//program counter
        int32_t ap=0;//address counter, can be negative
        for(pc=0;pc<program.size();pc++){
            if(skip){//if is skipping blocks
                if(program[pc]==OPERATOR_LBRACKET){//if it is a '[', add one to depth counter
                    skip_depth++;
                }else if(program[pc]==OPERATOR_RBRACKET){
                    if(skip_depth>0){//if it is a ']' and depth is greater than zero, subtract one from depth
                        skip_depth--;
                    }else{//if it is a ']' and depth is zero, skipping is finished
                        skip=false;
                    }
                }
                continue;
            }
            switch(program[pc]){
            case OPERATOR_MVRIGHT://move address pointer to the right
                ap++;
                break;
            case OPERATOR_MVLEFT://move address pointer to the left
                ap--;
                break;
            case OPERATOR_INCREMENT://increment value by one
                tape[ap]++;
                break;
            case OPERATOR_DECREMENT://decrement value by one
                tape[ap]--;
                break;
            case OPERATOR_PRINT://print character at pointer
                std::cout<<char(tape[ap]);
                break;
            case OPERATOR_READ://read input and store it in address
                tape[ap]=getchar();
                break;
            case OPERATOR_LBRACKET:
                if(tape[ap]==0){//skip past block if value is zero
                    skip=true;
                    skip_depth=0;
                }else{//if not zero, add current location to the stack
                    stack.push(pc);
                }
                break;
            case OPERATOR_RBRACKET:
                if(tape[ap]!=0){//if value is not zero, go back to the start of the block
                    pc=stack.top();
                }else{//if the value is zero, pop the stack and exit the block
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
