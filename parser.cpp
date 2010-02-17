#include <iostream>
#include "parser.h"
#include "scanner.h"
#include "node.h"

Parser::Parser(Scanner *scan)
{
    s = scan;
    s->next();
    SynExpr *e = ParseExpr();
    e->print(0);
}

SynExpr * Parser::ParseExpr()
{
    SynExpr * e = ParseTerm();
    if((s->get().getType()==ttPlus)||(s->get().getType()==ttMinus))
    {
        Token token = s->get();
        s->next();
        e = (SynExpr*)new SynBinOp(token, ParseExpr(), e);
    }
    return e;
}

SynExpr * Parser::ParseTerm()
{
    SynExpr * e = ParseFactor();
    if((s->get().getType()==ttAstr)||(s->get().getType()==ttDiv))
    {
        Token token = s->get();
        s->next();
        e = (SynExpr*)new SynBinOp(token, ParseFactor(), e);
    }
    return e;
}

SynExpr * Parser::ParseFactor()
{
    SynExpr * r;
    switch(s->get().getType())
    {
        case ttIdent:
                        r = (SynExpr*)new SynVar(s->get());
                        s->next();
                        return r;
        case ttInt:
        case ttInt16:
        case ttReal:
                        r = (SynExpr*)new SynConst(s->get());
                        s->next();
                        return r;
        case ttLeftBracket:
                        s->next();
                        r = ParseExpr();
                        if(s->get().getType()!=ttRightBracket) s->error(-10,"",s->getPos());
                        s->next();
                        return r;
    }
    return 0;
}
