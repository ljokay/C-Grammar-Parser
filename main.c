/*
    Landen Bock
    7/21/2024
    Recursive Parser
*/


#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "parser.h"

struct Token getToken() {
    int currentChar = 0;
    token.value = 0;
    //Discards whitespace
    while((currentChar = getchar()) == ' ');

    //Checks if character is a digit. If it is, converts it's value to the actual digit value.
    if (isdigit(currentChar)) {
        while(isdigit(currentChar)) {
            token.value = 10 * token.value + currentChar - '0';
            currentChar = getchar();
        };
        ungetc(currentChar, stdin);
        token.type = NUMBER;
        printf("%d NUMBER\n", token.value);
        return token;
    }

    //Identifies the current char
    switch (currentChar) {
        case '+':
            token.type = PLUS;
            printf("%s\n","+ PLUS");
            break;
        case '-':
            token.type = MINUS;
            printf("%s\n","- MINUS");
            break;
        case '/':
            token.type = DIVIDE;
            printf("%s\n","/ DIVIDE");
            break;
        case '*':
            token.type = MULT;
            printf("%s\n","* MULT");
            break;
        case '%':
            token.type = REMAINDER;
            printf("%s\n","%% REMAINDER");
            break;
        case '^':
            token.type = POWER;
            printf("%s\n","^ POWER");
            break;
        case '(':
            token.type = LPAREN;
            printf("%s\n","( LPAREN");
            break;
        case ')':
            token.type = RPAREN;
            printf("%s\n",") RPAREN");
            break;
        case 'EOF':
            token.type = EOL;
            break;
        default: 
            token.type = ERROR;
            break;
    }
    return token;
}

//Starts the parsing process.
void command() {
    int result = expr();
    printf("\n\nResult: %d\n", result);
}

//Continues from command()/ factor1() checks for PLUS or MINUS
int expr() {
    int result = term();
    while(token.type == PLUS || token.type == MINUS) {
        TokenType new = token.type;
        match(new);
        if (new == PLUS) {
            result += term();
        }
        if (new == MINUS) {
            result -= term();
        }
    }
    return result;
}

//Continues from expr() checks for MULT, DIVIDE, or REMAINDER
int term() {
    int result = power();
    while(token.type == MULT || token.type == DIVIDE || token.type == REMAINDER) {
        TokenType new = token.type;
        match(new);
        if (new == MULT) {
            result *= power();
        }
        if (new == DIVIDE) {
            result /= power();
        }
        if (new == REMAINDER) {
            result %= power();
        }
    }
    return result;
}

//Continues from term(). Checks for POWER
int power() {
    int result = factor();
    while(token.type == POWER) {
        match(POWER);
        result = pow(result, factor());
    }
    return result;
}

/*
Continues from power()
Checks for negative number, if non negative moves to the factor1() 
funciton with no change.
*/
int factor() {
    int result = factor1();
    if (token.type == MINUS) {
        match(MINUS);
        result -= factor1();
    }
    return result;
}


/*
Continues from factor() checks for parentheses.
If parentheses found, calls expr function and goes back through the rest.
*/
int factor1() {
    int result = 0;
    //Checks for parentheses
    if (token.type == LPAREN) {
        match(LPAREN);
        //Goes back to the expr() function and parses further
        result = expr();
        match(RPAREN);
    }
    //Checks for number
    else if (token.type == NUMBER) {
        result = token.value;
        match(NUMBER);
       
    }
    return result;
}

//Calls getToken to retrieve the token, then calls command() to begin parsing.
void parse() {
    getToken();
    command();
}

//Checks a new token type to see if it matches the global token variable type.
void match(TokenType newToken) {
    if (token.type == newToken) {
        token = getToken();
    }
    else {
//Prints an error message if there is no match
        printf("Match error\n");
    }
}

//Main method
int main() {
//Prompts user to enter input
    printf("Enter Expression: ");
//Input is then handled by the parse method.
    parse();
    return 0;
}