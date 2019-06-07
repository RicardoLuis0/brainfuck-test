#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <map>
#include <stack>
#include <cstdint>

#include "parser.h"

class Interpreter {
    public:
        Interpreter(std::string filename);
        void run();
    protected:
        std::vector<parse_output> program;//parse the program at argv[1]
        std::stack<uint32_t> stack;//stack, where the locations are stored during loops
        std::map<int32_t,uint8_t> tape;//tape, where the data is stored
        bool skip;//wether to skip block
        uint32_t skip_depth;//depth of current skip
        uint32_t pc;//program counter
        int32_t ap;//address counter, can be negative
    private:
};

#endif // INTERPRETER_H
