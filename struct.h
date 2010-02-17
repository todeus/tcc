#ifndef STRUCT_H
#define STRUCT_H

using namespace std;

enum TokenType
{
                ttNothing,
        //End Of File
                                ttEOF,
        //Identifiers adn Keywords
                                ttIdent,
                                ttKeyword,
        //Constants (Numeric, Char, String)
                                ttInt, ttReal, ttInt16,
                                ttChar,
                                ttString,
        //Operations +,-,*,/,%,++,--,&,|,&&,||, =,!=,!,==,>=,<=,+=,-=,*=,/=,%=,&=,|=,>>=,<<=,<<,>>,<,>
                ttPlus, ttMinus, ttAstr, ttDiv,
                ttMod, ttInc, ttDec, ttAmp,
                ttBitOr, ttAnd, ttOr, ttAssign,
                ttNotAssign, ttNot, ttEq, ttGreaterEq,
                ttLessEq, ttAddAssign, ttSubAssign, ttMulAssign,
                ttDivAssign, ttModAssign, ttBitAndAssign, ttBitOrAssign,
                ttShiftLeftAssign, ttShiftRightAssign, ttShiftLeft, ttShiftRight,
                ttLess,ttGreater, ttBitXor, ttBitXorAssign,
        //Separators , : ; . ( ) [ ] { }
                ttComma, ttColon, ttSemicolon, ttPoint,
                ttRightBracket, ttLeftBracket, ttRightSqBracket, ttLeftSqBracket,
                ttBegin, ttEnd

};

struct Pos
{
    int line;
    int position;
};

struct MyEx
{
    int code;
    std::string str;
    Pos pos;
};


#endif // STRUCT_H
