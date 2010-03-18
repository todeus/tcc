#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include "token.h"

class Scanner {
    private:
        Token token;
        std::ifstream in;
        Pos pos;
    public:
        Scanner(char * filename);
        ~Scanner();
        Token get();
        Token next();
        Pos getPos();
        void error(int error, string message,Pos pos);
};

#endif // SCANNER_H
