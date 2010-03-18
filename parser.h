#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "node.h"

class Parser
{
public:
    Scanner *s;
    Parser(Scanner *scan);
    SynExpr * ParseExpr();
    SynExpr * ParseAssignExpr();
    SynExpr * ParseLogOrExpr();
    SynExpr * ParseLogAndExpr();
    SynExpr * ParseBitOrExpr();
    SynExpr * ParseAndExpr();
    SynExpr * ParseEquExpr();
    SynExpr * ParseRelExpr();
    SynExpr * ParseShiftExpr();
    SynExpr * ParseAddExpr();
    SynExpr * ParseMulExpr();
    SynExpr * ParseFactor();

    SynExpr * ParseState();
    SynExpr * ParseBlock();
    SynExpr * ParseIf();
    SynExpr * ParseWhile();
    SynExpr * ParseVarDecl();
    SynExpr * ParseParam();
private:
    SynNode * obj;

};

#endif // PARSER_H
