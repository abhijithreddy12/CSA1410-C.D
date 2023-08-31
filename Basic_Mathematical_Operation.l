%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int yylex(void);

int yylval; // Value of the token (number or result of operation)
%}

%%
[0-9]+      { yylval = atoi(yytext); return 'n'; } // Return 'n' for numbers
[-+*/]      return yytext[0]; // Return operators
[ \t\n]    ; // Ignore whitespace and newlines
.          return yytext[0]; // Return any other character
%%

int yywrap() {return 1;}
int main() {
    int result = 0;
    int token;

    while ((token = yylex()) != 0) {
        if (token == 'n') {
            result = yylval;
        } else {
            int num = yylex(); // Get the next number
            switch (token) {
                case '+': result += num; break;
                case '-': result -= num; break;
                case '*': result *= num; break;
                case '/': result /= num; break;
            }
        }
    }

    printf("Result: %d\n", result);
    return 0;
}
