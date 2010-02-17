#include <iostream>
#include <fstream>
#include <sstream>

#include "scanner.h"
#include "KA.h"

using namespace std;

Scanner::Scanner(char * file)
{
    in.open(file);
    if(!in)
    {
        error(-1, file,pos);
    }
    pos.line = 1;
    pos.position = 1;
}

Scanner::~Scanner()
{
}


Token Scanner::get()
{
    return token;
}

Token Scanner::next()
{
    int curCond, condition;
    int x = 0;
    string buffer;
    condition = 0;
    while(x!=-1)
    {
        x = in.get();
        if(x>127)
        {
            stringstream st;
            st << x;
            error(0,st.str(),pos);
        }

        curCond = condition;
        condition = table[condition][x+1];

        if(condition==205)
        {
            return token.setToken(20,"EOF");
        }

        if(condition>201)
        {
            error(condition, "",pos);
        }

        if(x=='\n')
        {
            pos.line++;
            pos.position=0;
        }
        //If EOF
        if(condition==20)
        {
            return token.setToken(20,"EOF");
        }

        if(condition<200)
        {
            buffer+=x;
        } else {
            if(x=='\n')
            {
                pos.line--;
            }
            in.unget();
            //cout << pos.line << ": ";
            try
            {
                return token.setToken(curCond,buffer);
            } catch(int e) { error(e,"",pos);}
        }



        if(condition==0)
        {
            buffer="";
        }
        pos.position++;
    }

}

Pos Scanner::getPos()
{
    return pos;
}

void Scanner::error(int error, std::string message,Pos pos)
{
    MyEx e;
    e.code  = error;
    e.str   = message;
    e.pos   = pos;
    throw(e);
}
