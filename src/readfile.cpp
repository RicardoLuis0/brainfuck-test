#include "readfile.h"
#include <iostream>
#include <cstdio>
#include <stdexcept>

static long find_file_size(FILE * f){
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
