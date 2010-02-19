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
    SynExpr * e = ParseAssignExpr();
    return e;
}

SynExpr * Parser::ParseAssignExpr()
{
    SynExpr * e = ParseLogOrExpr();
    if(s->get().getType()==ttAssign)
    {
        while(s->get().getType()==ttAssign)
        {
            Token token = s->get();
            s->next();
            e = (SynExpr*)new SynBinOp(token, ParseLogOrExpr(), e);
        }
        return e;
    }
    return e;
}


SynExpr * Parser::ParseLogOrExpr()
{
    SynExpr * e = ParseLogAndExpr();
    if(s->get().getType()==ttOr)
    {
        while(s->get().getType()==ttOr)
        {
            Token token = s->get();
            s->next();
            e = (SynExpr*)new SynBinOp(token, ParseLogAndExpr(), e);
        }
        return e;
    }
    return e;
}


SynExpr * Parser::ParseLogAndExpr()
{
    SynExpr * e = ParseBitOrExpr();
    if(s->get().getType()==ttAnd)
    {
        while(s->get().getType()==ttAnd)
        {
            Token token = s->get();
            s->next();
            e = (SynExpr*)new SynBinOp(token, ParseBitOrExpr(), e);
        }
        return e;
    }
    return e;
}

SynExpr * Parser::ParseBitOrExpr()
{
    SynExpr * e = ParseAndExpr();
    if(s->get().getType()==ttBitOr)
    {
        while(s->get().getType()==ttBitOr)
        {
            Token token = s->get();
            s->next();
            e = (SynExpr*)new SynBinOp(token, ParseAndExpr(), e);
        }
        return e;
    }
    return e;
}

SynExpr * Parser::ParseAndExpr()
{
    SynExpr * e = ParseEquExpr();
    if(s->get().getType()==ttAmp)
    {
        while(s->get().getType()==ttAmp)
        {
            Token token = s->get();
            s->next();
            e = (SynExpr*)new SynBinOp(token, ParseEquExpr(), e);
        }
        return e;
    }
    return e;
}

SynExpr * Parser::ParseEquExpr()
{
    SynExpr * e = ParseRelExpr();
    if((s->get().getType()==ttNotAssign)||(s->get().getType()==ttEq))
    {
        while((s->get().getType()==ttNotAssign)||(s->get().getType()==ttEq))
        {
            Token token = s->get();
            s->next();
            e = (SynExpr*)new SynBinOp(token, ParseRelExpr(), e);
        }
        return e;
    }
    return e;
}

SynExpr * Parser::ParseRelExpr()
{
    SynExpr * e = ParseShiftExpr();
    if((s->get().getType()==ttGreaterEq)||
       (s->get().getType()==ttLessEq)||
       (s->get().getType()==ttLess)||
       (s->get().getType()==ttGreater))
    {
        while((s->get().getType()==ttGreaterEq)||
              (s->get().getType()==ttLessEq)||
              (s->get().getType()==ttLess)||
              (s->get().getType()==ttGreater))
        {
            Token token = s->get();
            s->next();
            e = (SynExpr*)new SynBinOp(token, ParseShiftExpr(), e);
        }
        return e;
    }
    return e;
}

SynExpr * Parser::ParseShiftExpr()
{
    SynExpr * e = ParseAddExpr();
    if((s->get().getType()==ttShiftLeft)||(s->get().getType()==ttShiftRight))
    {
        while((s->get().getType()==ttShiftLeft)||(s->get().getType()==ttShiftRight))
        {
            Token token = s->get();
            s->next();
            e = (SynExpr*)new SynBinOp(token, ParseAddExpr(), e);
        }
        return e;
    }
    return e;
}

SynExpr * Parser::ParseAddExpr()
{
    SynExpr * e = ParseMulExpr();
    if((s->get().getType()==ttPlus)||(s->get().getType()==ttMinus))
    {
        while ((s->get().getType()==ttPlus)||(s->get().getType()==ttMinus))
        {
            Token token = s->get();
            s->next();
            e = (SynExpr*)new SynBinOp(token, ParseMulExpr(), e);
        }
        return e;
    }
    return e;
}


SynExpr * Parser::ParseMulExpr()
{
    SynExpr * e = ParseFactor();
    if((s->get().getType()==ttAstr)||
       (s->get().getType()==ttDiv)||
       (s->get().getType()==ttMod))
    {
        while((s->get().getType()==ttAstr)||
              (s->get().getType()==ttDiv)||
              (s->get().getType()==ttMod))
        {
            Token token = s->get();
            s->next();
            e = (SynExpr*)new SynBinOp(token, ParseFactor(), e);
        }
        return e;
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
       case ttPlus:
       case ttMinus:
       case ttNot:
       case ttInc:
       case ttDec:
                        Token token = s->get();
                        s->next();
                        r = (SynExpr*)new SynUnOp(token, ParseExpr());
                        return r;
    }
    return 0;
}
