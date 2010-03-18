#ifndef NODE_H
#define NODE_H

#include <vector>
#include "scanner.h"

class SynNode
{
public:
    SynNode();
    ~SynNode();
    virtual void print(int n);
};

class SynExpr:public SynNode
{
public:
    SynExpr();
    ~SynExpr();
};


class SynWhile:public SynExpr
{
public:
    SynWhile(SynNode* con, SynNode* op);
    ~SynWhile();
    void print(int n);
private:
    SynNode * condition;
    SynNode * operation;
};

class SynIf:public SynExpr
{
public:
    SynIf(SynNode* con, SynNode* op, SynNode* alt_op);
    ~SynIf();
    void print(int n);
private:
    SynNode * condition;
    SynNode * operation;
    SynNode * alt_operation;
};

class SynVarDecl:public SynExpr
{
public:
    SynVarDecl(Token tp, Token t, SynNode* p, SynNode* b);
    ~SynVarDecl();
    void print(int n);
private:
    Token name;
    Token type;
    SynNode * param;
    SynNode * body;
};


class SynBlock:public SynExpr
{
public:
    SynBlock();
    ~SynBlock();
    void print(int n);
    void push_back(SynNode* st);
    vector <SynNode*> body;
    int x;
//private:

};

class SynBlockParam:public SynExpr
{
public:
    SynBlockParam();
    ~SynBlockParam();
    void print(int n);
    void push_back(SynNode* st);
    vector <SynNode*> body;
    int x;
//private:

};


class SynBinOp:public SynExpr
{
public:
    SynBinOp(Token t, SynNode* l, SynNode* r);
    ~SynBinOp();
    void print(int n);
private:
    SynNode * left;
    SynNode * right;
    Token token;

};

class SynUnOp:public SynExpr
{
public:
    SynUnOp(Token t, SynNode* l);
    ~SynUnOp();
    void print(int n);
private:
    SynNode * left;
    Token token;

};

class SynVar:public SynExpr
{
public:
    SynVar(Token t);
    ~SynVar();
    void print(int n);
private:
    Token token;

};
class SynConst:public SynExpr
{
public:
    SynConst(Token t);
    ~SynConst();
    void print(int n);
private:
    Token token;

};

#endif // NODE_H
