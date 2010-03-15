#include <iostream>
#include <sstream>
#include "node.h"

using namespace std;

void SynNode::print(int n)
{
}

SynExpr::SynExpr()
{
    left = 0;
    right = 0;
}
SynExpr::~SynExpr()
{
}

/*
SynState::SynState()
{
    left = 0;
    right = 0;
}

SynState::~SynState()
{
}
*/

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
    left = 0;
    right = 0;
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
    left = 0;
    right = 0;
    token = t;
}
SynConst::~SynConst()
{
}
void SynConst::print(int n)
{
    cout << "[" << token.getSource() << "]" << endl;
}

SynWhile::SynWhile(SynNode* l, SynNode* r)
{
    left = l;
    right = r;
}
SynWhile::~SynWhile()
{
}

void SynWhile::print(int n)
{
    cout << "[WHILE]" << endl;

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
