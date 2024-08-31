#include <stdio.h>
#ifndef HTOI_H
#define HTOI_H

//TokenType enumeration
typedef enum { 
    PLUS,
    MINUS,
    DIVIDE,
    MULT,
    REMAINDER,
    POWER,
    LPAREN,
    RPAREN,
    NUMBER,
    ERROR,
    EOL
} TokenType;

//Token struct
struct Token {
    TokenType type;
    int value;
};
struct Token token;

struct Token getToken();
void command();
int expr();
int term();
int power();
int factor();
int factor1();
void parse();
void match(TokenType newToken);

#endif 