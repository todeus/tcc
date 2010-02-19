#include <iostream>
#include <sstream>
#include "node.h"

using namespace std;

SynExpr::SynExpr()
{
    left = 0;
    right = 0;
}
int SynExpr::print(int n)
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
SynExpr::~SynExpr()
{
}

SynState::SynState()
{
}

SynState::~SynState()
{
}
/*
SynFor::SynFor(SynState * par1, SynExpr * par2, SynState * par3, SynState * par4)
{
}
*/


SynBinOp::SynBinOp(Token t, SynExpr* l, SynExpr* r)
{
    left = l;
    right = r;
    token = t;
}

SynBinOp::~SynBinOp()
{
}

SynUnOp::SynUnOp(Token t, SynExpr* l)
{
    left = l;
    token = t;
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

SynConst::SynConst(Token t)
{
    left = 0;
    right = 0;
    token = t;
}
SynConst::~SynConst()
{
}
