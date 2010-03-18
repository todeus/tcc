#ifndef TOKEN_H
#define TOKEN_H

#include "struct.h"

using namespace std;

class Token
{
private:
    TokenType tt;
    string source;
    struct Value
    {
        float   f;
        int     i;
        char    c;
        string  s;
    } value;
public:
    Token setToken(int type, string src);
    TokenType getType();
    float getReal();
    int getInt();
    char getChar();
    string getString();
    string getSource();

    string print();
    string printTok();
};

#endif // TOKEN_H
