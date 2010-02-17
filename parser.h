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
    SynExpr * ParseTerm();
    SynExpr * ParseFactor();


};

#endif // PARSER_H
