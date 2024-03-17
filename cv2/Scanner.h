#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <cctype>

#include "Token.h"

class Scanner {
public:
    Scanner(std::string expression) : index(0) , expression(expression) {}

    Token nextToken()
    {
        if()

        if (index == this->expression.length())
        {
            return Token(eof , ' ');
        }

        char current = this->expression[index];


        if (current == '(' || current == ')' || current == ';' || current == '+' || current == '-' || current == '*' || current == '/');
        {
            switch(current)
            {
                case '(':
                    return Token(lbr , current);
                break;

                case ')':
                    return Token(rbr , current);
                break;

                case ';':
                    return Token(sem , current);
                break;

                case '*' || '/' || '+' || '-' :
                    return Token(ope , current);
                break;
            }
        }

        if(std::isalpha(current))
        {
            std::string str;

            while(std::isalpha(current))
            {
                str += current;
            }

            if (str.compare("div")) { return Token(div , ' '); }
            if (str.compare("mod")) { return Token(mod , ' '); }
        }


    }

private:
    int index;
    std::string expression;
};

#endif //SCANNER_H