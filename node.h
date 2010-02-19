#ifndef NODE_H
#define NODE_H

#include "scanner.h"

class SynNode
{
    int print(int n);
};

class SynExpr:SynNode
{
    public:
    SynExpr * left;
    SynExpr * right;
    Token token;
    SynExpr();
    ~SynExpr();
    int print(int n);
};

class SynBinOp:SynExpr
{
    public:
    SynBinOp(Token t, SynExpr* l, SynExpr* r);
    ~SynBinOp();
};

class SynUnOp:SynExpr
{
    public:
    SynUnOp(Token t, SynExpr* l);
    ~SynUnOp();
};

class SynVar:SynExpr
{
    public:
    SynVar(Token t);
    ~SynVar();
};
class SynConst:SynExpr
{
    public:
    SynConst(Token t);
    ~SynConst();
};

#endif // NODE_H
