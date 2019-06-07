#include "Interpreter.h"

#include "readfile.h"

#include <iostream>

Interpreter::Interpreter(std::string filename):program(parse(readfile(filename))),skip(false),skip_depth(0),pc(0),ap(0){
    
}

void Interpreter::run(){
    for(pc=0;pc<program.size();pc++){
        switch(program[pc].op){
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
                pc=program[pc].num;
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
        case OPERATOR_INVALID:
            throw std::runtime_error("Invalid operator");
        }
    }
}
