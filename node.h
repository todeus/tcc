#ifndef NODE_H
#define NODE_H

#include "scanner.h"

class SynNode
{
    public:
    virtual void print(int n);
};

/*
class SynState:public SynNode
{
    public:
    SynNode* left;
    SynNode* right;
    SynState();
    ~SynState();
};
*/

class SynExpr:public SynNode
{
    public:
    SynNode * left;
    SynNode * right;
    Token token;
    SynExpr();
    ~SynExpr();
};


class SynWhile:public SynExpr
{
    public:
    SynWhile(SynNode* l, SynNode* r);
    ~SynWhile();
    void print(int n);
};


class SynBinOp:public SynExpr
{
    public:
    SynBinOp(Token t, SynNode* l, SynNode* r);
    ~SynBinOp();
    void print(int n);
};

class SynUnOp:public SynExpr
{
    public:
    SynUnOp(Token t, SynNode* l);
    ~SynUnOp();
    void print(int n);
};

class SynVar:public SynExpr
{
    public:
    SynVar(Token t);
    ~SynVar();
    void print(int n);
};
class SynConst:public SynExpr
{
    public:
    SynConst(Token t);
    ~SynConst();
    void print(int n);
};

#endif // NODE_H
