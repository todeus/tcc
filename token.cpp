#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "token.h"

using namespace std;

//Replace in string
inline std::string replace(std::string text, std::string s, std::string d)
{
  for(unsigned index=0; index=text.find(s, index), index!=std::string::npos;)
  {
    text.replace(index, s.length(), d);
    index+=d.length();
  }
  return text;
}

Token Token::setToken(int type, string src)
{
    source = src;
    switch(type)
    {
        case 1:     tt = ttInt;         break;
        case 2:
        case 5:     tt = ttReal;        break;
        case 6:
        if(
            (src=="break")||
            (src=="char")||
            (src=="continue")||
            (src=="do")||
            (src=="else")||
            (src=="enum")||
            (src=="float")||
            (src=="for")||
            (src=="goto")||
            (src=="if")||
            (src=="int")||
            (src=="return")||
            (src=="sizeof")||
            (src=="struct")||
            (src=="typedef")||
            (src=="void")||
            (src=="while")
        )
        {
            tt = ttKeyword;
        } else {
            tt = ttIdent;
        }
        break;
        case 7:     tt = ttAssign;      break;
        case 9:     tt = ttDiv;         break;
        case 11:    tt = ttBitOr;       break;
        case 12:    tt = ttOr;          break;
        case 13:    tt = ttAmp;         break;
        case 14:    tt = ttAnd;         break;
        case 15:    tt = ttComma;       break;
        case 18:
        case 19:    tt = ttString;      break;
        case 20:    tt = ttEOF;         break;
        case 22:    tt = ttPlus;        break;
        case 23:    tt = ttInc;         break;
        case 24:    tt = ttAddAssign;   break;
        case 25:    tt = ttMinus;       break;
        case 26:    tt = ttDec;         break;
        case 27:    tt = ttSubAssign;   break;
        case 28:    tt = ttLess;        break;
        case 29:    tt = ttShiftLeft;   break;
        case 30:    tt = ttLessEq;      break;
        case 31:    tt = ttGreater;     break;
        case 32:    tt = ttShiftRight;  break;
        case 33:    tt = ttGreaterEq;   break;
        case 34:    tt = ttPoint;       break;
        case 41:    tt = ttAstr;        break;
        case 42:    tt = ttMulAssign;   break;
        case 43:    tt = ttEq;          break;
        case 44:    tt = ttNot;         break;
        case 45:    tt = ttNotAssign;   break;
        case 46:    tt = ttDivAssign;   break;
        case 47:    tt = ttMod;         break;
        case 48:    tt = ttModAssign;   break;
        case 50:    tt = ttChar;        break;
        case 51:    tt = ttBitAndAssign;break;
        case 52:    tt = ttBitOrAssign; break;
        case 53:    tt = ttBitXor;      break;
        case 54:    tt = ttBitXorAssign;break;
        case 55:    tt = ttShiftLeftAssign;break;
        case 56:    tt = ttShiftRightAssign;break;
        case 57:    tt = ttColon;       break;
        case 58:    tt = ttSemicolon;   break;
        case 59:    tt = ttLeftBracket;break;
        case 60:    tt = ttRightBracket; break;
        case 61:    tt = ttLeftSqBracket;break;
        case 62:    tt = ttRightSqBracket;break;
        case 63:    tt = ttBegin;       break;
        case 64:    tt = ttEnd;         break;
        case 65:
        case 66:    tt = ttInt16;       break;
    }
    switch(tt)
    {
        case ttReal:
            value.f = atof(src.c_str());
            if(isinf(value.f)) throw(1);
        break;

        case ttInt:
            if(strtol(src.c_str(),NULL,10)==LONG_MAX) throw(1);
            value.i = strtol(src.c_str(),NULL,10);
        break;

        case ttInt16:
            if(strtol(src.c_str(),NULL,16)==LONG_MAX) throw(1);
            value.i = strtol(src.c_str(),NULL,16);
        break;


        case ttChar:
            value.s = src.erase(0,1);
            value.s = value.s.erase(src.size()-1,1);
            value.s = replace(value.s, "\\0","\0");
            value.s = replace(value.s, "\\\\","\\");
            value.s = replace(value.s, "\\\"","\"");
            value.s = replace(value.s, "\\'","\'");
            value.s = replace(value.s, "\\n","\n");
            value.s = replace(value.s, "\\r","\r");
            value.s = replace(value.s, "\\b","\b");
            value.s = replace(value.s, "\\t","\t");
            value.s = replace(value.s, "\\a","\a");
            value.s = replace(value.s, "\\v","\v");
            value.c = value.s.c_str()[0];
        break;

        case ttString:
            value.s = src.erase(0,1);
            value.s = value.s.erase(src.size()-1,1);
            value.s = replace(value.s, "\\0","\0");
            value.s = replace(value.s, "\\\\","\\");
            value.s = replace(value.s, "\\\"","\"");
            value.s = replace(value.s, "\\'","\'");
            value.s = replace(value.s, "\\n","\n");
            value.s = replace(value.s, "\\r","\r");
            value.s = replace(value.s, "\\b","\b");
            value.s = replace(value.s, "\\t","\t");
            value.s = replace(value.s, "\\a","\a");
            value.s = replace(value.s, "\\v","\v");
        break;
    }

    return *this;
}

float Token::getReal()
{
    return value.f;
}

int Token::getInt()
{
    return value.i;
}

char Token::getChar()
{
    return value.c;
}

string Token::getString()
{
    return value.s;
}

TokenType Token::getType()
{
    return tt;
}

string Token::printTok()
{
    stringstream tmp;
    switch(tt)
    {
        case ttInt:
        case ttInt16:   tmp << value.i;         break;
        case ttReal:    tmp << value.f;         break;
        case ttChar:    tmp << value.c;         break;
        case ttString:  tmp << value.s;         break;
        default:        tmp << source;          break;
    }
    return tmp.str();
}

string Token::getSource()
{
    return source;
}

string Token::print()
{
    char * type;
    switch(tt)
    {
        case ttEOF:         type="EOF";             break;
        case ttInt:         type="Integer";         break;
        case ttReal:        type="Float";            break;
        case ttIdent:       type="Identifier";      break;
        case ttAssign:      type="Assign";          break;
        case ttDiv:         type="Division";        break;
        case ttBitOr:       type="BitOr";           break;
        case ttOr:          type="Or";              break;
        case ttAmp:         type="Amp";             break;
        case ttAnd:         type="And";             break;
        case ttString:      type="String";          break;
        case ttPlus:        type="Plus";            break;
        case ttInc:         type="Increment";       break;
        case ttAddAssign:   type="AddAssign";       break;
        case ttMinus:       type="Minus";           break;
        case ttDec:         type="Decrement";       break;
        case ttSubAssign:   type="SubAssign";       break;
        case ttLess:        type="Less";            break;
        case ttShiftLeft:   type="ShiftL";          break;
        case ttLessEq:      type="LessEq";          break;
        case ttGreater:     type="Greather";        break;
        case ttShiftRight:  type="ShiftR";          break;
        case ttGreaterEq:   type="GreatherEq";      break;
        case ttPoint:       type="Point";           break;
        case ttAstr:        type="Astr";            break;
        case ttMulAssign:   type="MulAssign";       break;
        case ttEq:          type="Equally";         break;
        case ttNot:         type="Not";             break;
        case ttNotAssign:   type="NotAssign";       break;
        case ttDivAssign:   type="DivAssign";       break;
        case ttMod:         type="Mod";             break;
        case ttModAssign:   type="ModAssign";       break;
        case ttChar:        type="Char";            break;
        case ttBitAndAssign:type="BitAndAssign";    break;
        case ttBitOrAssign: type="BitOrAssign";     break;
        case ttBitXor:      type="BitXor";          break;
        case ttBitXorAssign:type="BitXorAssign";    break;
        case ttShiftLeftAssign:type="ShiftLAssign"; break;
        case ttShiftRightAssign:type="ShiftRAssign";break;
        case ttComma:       type="Comma";           break;
        case ttColon:       type="Colon";           break;
        case ttSemicolon:   type="Semicolon";       break;
        case ttRightBracket:type="RightBracket";    break;
        case ttLeftBracket: type="LeftBracket";     break;
        case ttRightSqBracket:type="RightSqBracket";break;
        case ttLeftSqBracket:type="LeftSqBracket";  break;
        case ttBegin:       type="Begin";           break;
        case ttEnd:         type="End";             break;
        case ttKeyword:     type="Keyword";         break;
        case ttInt16:       type="Int16";       break;
        default:            type="NO";              break;

    }
    stringstream tmp;
    tmp << source << "\t\t" << type << "\t\t";
    switch(tt)
    {
        case ttInt:
        case ttInt16:   tmp << "Value: " << value.i;                                            break;
        case ttReal:    tmp << "Value: " << value.f;                                            break;
        case ttChar:    tmp << "Value: " << value.c << "\t\t(int)Char: " << (int)value.c;         break;
        case ttString:  tmp << "Value: " << value.s;                                            break;
        default:        tmp << "";                                                              break;
    }
    return tmp.str();
}
