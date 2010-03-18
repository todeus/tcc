#include <iostream>
#include "parser.h"
#include "scanner.h"
#include "node.h"

Parser::Parser(Scanner *scan)
{
    s = scan;
    s->next();
    obj = ParseState();
    obj->print(0);
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
    if((s->get().getType()==ttNotAssign)||(s->get().getType()==ttEq)||
        (s->get().getType()==ttAddAssign)||(s->get().getType()==ttSubAssign)||
        (s->get().getType()==ttMulAssign)||(s->get().getType()==ttDivAssign)||
        (s->get().getType()==ttModAssign)
        )
    {
        while((s->get().getType()==ttNotAssign)||(s->get().getType()==ttEq)||
            (s->get().getType()==ttAddAssign)||(s->get().getType()==ttSubAssign)||
            (s->get().getType()==ttMulAssign)||(s->get().getType()==ttDivAssign)||
            (s->get().getType()==ttModAssign)
            )
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
                        if(s->get().getType()!=ttRightBracket) s->error(-12,"",s->getPos());
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

SynExpr * Parser::ParseState()
{
    SynNode * r;

    if(
            (s->get().getSource() == "int")||
            (s->get().getSource() == "float")||
            (s->get().getSource() == "void")
        )
        return ParseVarDecl();
    if(s->get().getSource() == "while") return ParseWhile();
    if(s->get().getSource() == "do") return ParseDo();
    if(s->get().getSource() == "for") return ParseFor();
    if(s->get().getSource() == "if") return ParseIf();
    if(s->get().getType() == ttBegin) return ParseBlock();
    else
    {
        r = ParseExpr();
        if(s->get().getType()!=ttSemicolon) s->error(-15,"",s->getPos());
        s->next();
        return (SynExpr*)r;
    }
}

SynExpr * Parser::ParseVarDecl()
{
    Token name;
    Token type;
    Token value_;
    SynNode * param;
    SynNode * body;

    type = s->get();
    s->next();
    name = s->get();
    s->next();
    if(s->get().getType()==ttLeftBracket)
    {
        param = ParseParam();
        if(s->get().getType()!=ttBegin) s->error(-13,"",s->getPos());
        body = ParseBlock();

    }
    else
    {
        param = NULL;
        body = NULL;

        if(s->get().getType()==ttAssign)
        {
            s->next();
            if((s->get().getType()==ttInt)||(s->get().getType()==ttInt16)||(s->get().getType()==ttReal))
                value_=s->get();
            else
                s->error(-8,"",s->getPos());
        }
    }
    s->next();
    return new SynVarDecl(type,name,value_,param,body);
}

SynExpr * Parser::ParseParam()
{
    SynBlockParam * block;
    SynNode * st;

    s->next();
    block = new SynBlockParam();
    while(s->get().getType()!=ttRightBracket)
    {
        if(s->get().getType()!=ttKeyword) s->error(-10,"",s->getPos());
        st = ParseVarDecl();
        block->push_back(st);
        if((s->get().getType()!=ttRightBracket)&&(s->get().getType()!=ttComma)) s->error(-14,"",s->getPos());
        if(s->get().getType()==ttComma)
        {
            s->next();
        }
    }
    s->next();
    return (SynExpr*)block;
}

SynExpr * Parser::ParseBlock()
{
    SynBlock * block;
    SynNode * st;

    s->next();
    block = new SynBlock();
    while(s->get().getType()!=ttEnd)
    {
        st = ParseState();
        block->push_back(st);
    }
    s->next();
    return (SynExpr*)block;
}

SynExpr * Parser::ParseIf()
{
    SynNode * condition;
    SynNode * operation;
    SynNode * alt_operation;

    s->next();
    if(s->get().getType()!=ttLeftBracket) s->error(-11,"",s->getPos());
    s->next();
    condition = ParseExpr();
    if(s->get().getType()!=ttRightBracket) s->error(-12,"",s->getPos());
    s->next();
    operation = ParseState();
    if(s->get().getSource() == "else")
    {
        s->next();
        alt_operation = ParseState();
        return (SynExpr*)new SynIf(condition,operation,alt_operation);
    }


    return (SynExpr*)new SynIf(condition,operation,NULL);

}


SynExpr * Parser::ParseWhile()
{
    SynNode * condition;
    SynNode * operation;

    s->next();
    if(s->get().getType()!=ttLeftBracket) s->error(-11,"",s->getPos());
    s->next();
    condition = ParseExpr();
    if(s->get().getType()!=ttRightBracket) s->error(-12,"",s->getPos());
    s->next();
    operation = ParseState();

    return (SynExpr*)new SynWhile(condition,operation);

}

SynExpr * Parser::ParseDo()
{
    SynNode * condition;
    SynNode * operation;

    s->next();
    operation = ParseState();
    if(s->get().getSource()!="while") s->error(-9,"",s->getPos());
    s->next();
    if(s->get().getType()!=ttLeftBracket) s->error(-11,"",s->getPos());
    s->next();
    condition = ParseExpr();
    if(s->get().getType()!=ttRightBracket) s->error(-12,"",s->getPos());
    s->next();
    if(s->get().getType()!=ttSemicolon) s->error(-15,"",s->getPos());


    return (SynExpr*)new SynDo(condition,operation);

}

SynExpr * Parser::ParseFor()
{
    SynNode * condition1;
    SynNode * condition2;
    SynNode * condition3;
    SynNode * operation;

    s->next();
    if(s->get().getType()!=ttLeftBracket) s->error(-11,"",s->getPos());
    s->next();
    condition1 = ParseVarDecl();

    if(s->get().getType()!=ttSemicolon) s->error(-15,"",s->getPos());
    s->next();
    condition2 = ParseExpr();

    if(s->get().getType()!=ttSemicolon) s->error(-15,"",s->getPos());
    s->next();
    condition3 = ParseExpr();


    if(s->get().getType()!=ttRightBracket) s->error(-12,"",s->getPos());
    s->next();
    operation = ParseState();

    return (SynExpr*)new SynFor(condition1,condition2,condition3,operation);

}
