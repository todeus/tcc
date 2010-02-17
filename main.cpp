#include <iostream>
#include <fstream>

#include "scanner.h"
#include "parser.h"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc==1)
    {
        std::cout << "*****************************" << std::endl;
        std::cout << "      Todeus C Compiler      " << std::endl;
        std::cout << "                             " << std::endl;
        std::cout << "  Author: Mikhail S. Pavlov  " << std::endl;
        std::cout << "                             " << std::endl;
        std::cout << "           Group: 238        " << std::endl;
        std::cout << "*****************************" << std::endl;
    }

    //if(argc==2)
    {
        try
        {
            Scanner * s = new Scanner("test11.txt");

            /*
            //Вывод результата работы лексического анализатора(список лексем)
            while(s->next().getType()!=ttEOF)
            {
                std::cout << s->get().print() << endl;
            }
            */


            Parser * p = new Parser(s);


        } catch(MyEx error) {
            switch(error.code)
            {
                case -1:    cout << "Error: File \'" << error.str << "\' not found!"; break;
                case 0:     cout << "Error: Unknown symbol \'"<< error.str <<"\'!"; break;
                case 1:     cout << "Error(" << error.pos.line << "," << error.pos.position << "): Constant is too long!"; break;
                case 202:   cout << "Error(" << error.pos.line << "," << error.pos.position << "): Unclosed string literal!"; break;
                case 203:   cout << "Error(" << error.pos.line << "," << error.pos.position << "): Error in numeric constant!"; break;
                case 204:   cout << "Error(" << error.pos.line << "," << error.pos.position << "): Error in char constant!"; break;
                case 206:   cout << "Error(" << error.pos.line << "," << error.pos.position << "): Error escape ...!"; break;
                default:    cout << "Error: Unknown error!"; break;
            }
        }
    }

    return 0;

}
