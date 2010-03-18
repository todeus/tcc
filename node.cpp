#include <iostream>
#include <sstream>
#include "node.h"

using namespace std;

void SynNode::print(int n)
{
}

SynNode::SynNode()
{
}
SynNode::~SynNode()
{
}

SynExpr::SynExpr()
{
}
SynExpr::~SynExpr()
{
}

SynBinOp::SynBinOp(Token t, SynNode* l, SynNode* r)
{
    left = l;
    right = r;
    token = t;
}

SynBinOp::~SynBinOp()
{
}

void SynBinOp::print(int n)
{
    cout << "[" << token.getSource() << "]" << endl;
    if(left)
    {
        for(int i=0;i<n;i++)
            cout<<"   ";
        cout<<" '-";
        left->print(n+1);
    }
    if(right)
    {
        for(int i=0;i<n;i++)
            cout<<"   ";
        cout<<" '-";
        right->print(n+1);
    }
}

SynUnOp::SynUnOp(Token t, SynNode* l)
{
    left = l;
    token = t;
}

void SynUnOp::print(int n)
{
    cout << "[" << token.getSource() << "]" << endl;
    if(left)
    {
        for(int i=0;i<n;i++)
            cout<<"   ";
        cout<<" '-";
        left->print(n+1);
    }
}

SynUnOp::~SynUnOp()
{
}


SynVar::SynVar(Token t)
{
    token = t;
}
SynVar::~SynVar()
{
}

void SynVar::print(int n)
{
    cout << "[" << token.getSource() << "]" << endl;
}

SynConst::SynConst(Token t)
{
    token = t;
}
SynConst::~SynConst()
{
}
void SynConst::print(int n)
{
    cout << "[" << token.getSource() << "]" << endl;
}

SynWhile::SynWhile(SynNode* con, SynNode* op)
{
    condition = con;
    operation = op;
}
SynWhile::~SynWhile()
{
}

void SynWhile::print(int n)
{
    cout << "[WHILE]" << endl;

    if(condition)
    {
        for(int i=0;i<n;i++)
            cout<<"   ";
        cout<<" '-";
        condition->print(n+1);
    }
    if(operation)
    {
        for(int i=0;i<n;i++)
            cout<<"   ";
        cout<<" '-";
        operation->print(n+1);
    }

}

SynDo::SynDo(SynNode* con, SynNode* op)
{
    condition = con;
    operation = op;
}
SynDo::~SynDo()
{
}

void SynDo::print(int n)
{
    cout << "[DO]" << endl;

    if(condition)
    {
        for(int i=0;i<n;i++)
            cout<<"   ";
        cout<<" '-";
        condition->print(n+1);
    }
    if(operation)
    {
        for(int i=0;i<n;i++)
            cout<<"   ";
        cout<<" '-";
        operation->print(n+1);
    }

}

SynIf::SynIf(SynNode* con, SynNode* op, SynNode* alt_op)
{
    condition = con;
    operation = op;
    alt_operation = alt_op;
}
SynIf::~SynIf()
{
}

void SynIf::print(int n)
{
    cout << "[IF]" << endl;

    if(condition)
    {
        for(int i=0;i<n;i++)
            cout<<"   ";
        cout<<" '-";
        condition->print(n+1);
    }
    if(operation)
    {
        for(int i=0;i<n;i++)
            cout<<"   ";
        cout<<" '-";
        operation->print(n+1);
    }
    if(alt_operation)
    {
        for(int i=0;i<n;i++)
            cout<<"   ";
        cout<<" '-";
        alt_operation->print(n+1);
    }

}

SynFor::SynFor(SynNode* con1, SynNode* con2, SynNode* con3, SynNode* op)
{
    condition1 = con1;
    condition2 = con2;
    condition3 = con3;
    operation = op;
}
SynFor::~SynFor()
{
}

void SynFor::print(int n)
{
    cout << "[FOR]" << endl;

    if(condition1)
    {
        for(int i=0;i<n;i++)
            cout<<"   ";
        cout<<" '-";
        condition1->print(n+1);
    }
    if(condition2)
    {
        for(int i=0;i<n;i++)
            cout<<"   ";
        cout<<" '-";
        condition2->print(n+1);
    }
    if(condition3)
    {
        for(int i=0;i<n;i++)
            cout<<"   ";
        cout<<" '-";
        condition3->print(n+1);
    }

    if(operation)
    {
        for(int i=0;i<n;i++)
            cout<<"   ";
        cout<<" '-";
        operation->print(n+1);
    }

}



SynBlock::SynBlock()
{
}
SynBlock::~SynBlock()
{
}
void SynBlock::push_back(SynNode *st)
{
    body.push_back(st);
}
void SynBlock::print(int n)
{
    SynNode * c;

    cout << "[BLOCK {...}]" << endl;

    while(!body.empty())
    {
        c = body.back();
        if(c)
        {
            for(int i=0;i<n;i++)
                cout<<"   ";
            cout<<" '-";
            c->print(n+1);
        }
        body.pop_back();
    }

}


SynBlockParam::SynBlockParam()
{
}
SynBlockParam::~SynBlockParam()
{
}
void SynBlockParam::push_back(SynNode *st)
{
    body.push_back(st);
}
void SynBlockParam::print(int n)
{
    SynNode * c;

    cout << "[BLOCK (...)]" << endl;

    while(!body.empty())
    {
        c = body.back();
        if(c)
        {
            for(int i=0;i<n;i++)
                cout<<"   ";
            cout<<" '-";
            c->print(n+1);
        }
        body.pop_back();
    }

}

SynVarDecl::SynVarDecl(Token tp ,Token t, Token val, SynNode *p, SynNode *b)
{
    name = t;
    param = p;
    value_ = val;
    body = b;
    type = tp;
}
SynVarDecl::~SynVarDecl()
{
}

void SynVarDecl::print(int n)
{
        cout << "[DECLARATION]" << endl;
        for(int i=0;i<n;i++)
            cout<<"   ";
        cout<<" '-[" << type.getSource() << "]" << endl;

        for(int i=0;i<n;i++)
            cout<<"   ";
        cout<<" '-[" << name.getSource() << "]" << endl;
        if(value_.getSource()!="")
        {
            for(int i=0;i<n;i++)
                cout<<"   ";
            cout<<" '-[" << value_.getSource() << "]" << endl;
        }
    if(param)
    {
        for(int i=0;i<n;i++)
            cout<<"   ";
        cout<<" '-";
        param->print(n+1);
    }
    if(body)
    {
        for(int i=0;i<n;i++)
            cout<<"   ";
        cout<<" '-";
        body->print(n+1);
    }
}
