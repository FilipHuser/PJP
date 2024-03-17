#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenEnum {
    eof, //""
    ope, //operator
    lbr, //left bracket
    rbr, //right bracket
    num, //number
    div, //division
    mod, //modulo
    sem, //semicolon ;
};


class Token {
public:
    Token(TokenEnum te , char c) : tokenEnum(te) , c(c) {}
private:
    TokenEnum tokenEnum;
    char c;
};

#endif //TOKEN_H