#include <iostream>
#include <stdexcept>
#include "Interpreter.h"

int main(int argc,char ** argv){
    if(argc<2){
        std::cout<<"Missing File Argument, usage: program \"file\"\n";
        return 1;
    }
    try{
        Interpreter p(argv[1]);
        p.run();
    }catch(std::exception &e){
        std::cout<<"failed with exception:\n  "<<e.what()<<"\n";
        return 1;
    }
}
