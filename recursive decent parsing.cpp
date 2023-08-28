#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

// Function prototypes for recursive descent parsing
bool parseExpression(const char *input, int *pos, int *result);
bool parseTerm(const char *input, int *pos, int *result);
bool parseFactor(const char *input, int *pos, int *result);

// Function to skip whitespace characters
void skipWhitespace(const char *input, int *pos) {
    while (input[*pos] == ' ' || input[*pos] == '\t' || input[*pos] == '\n') {
        (*pos)++;
    }
}

// Recursive Descent Parsing for expressions
bool parseExpression(const char *input, int *pos, int *result) {
    skipWhitespace(input, pos);

    int term1;
    if (!parseTerm(input, pos, &term1)) {
        return false;
    }

    skipWhitespace(input, pos);

    while (input[*pos] == '+' || input[*pos] == '-') {
        char op = input[(*pos)++];
        int term2;

        if (!parseTerm(input, pos, &term2)) {
            return false;
        }

        if (op == '+') {
            term1 += term2;
        } else {
            term1 -= term2;
        }

        skipWhitespace(input, pos);
    }

    *result = term1;
    return true;
}

// Recursive Descent Parsing for terms
bool parseTerm(const char *input, int *pos, int *result) {
    skipWhitespace(input, pos);

    int factor1;
    if (!parseFactor(input, pos, &factor1)) {
        return false;
    }

    skipWhitespace(input, pos);

    while (input[*pos] == '*' || input[*pos] == '/') {
        char op = input[(*pos)++];
        int factor2;

        if (!parseFactor(input, pos, &factor2)) {
            return false;
        }

        if (op == '*') {
            factor1 *= factor2;
        } else {
            if (factor2 == 0) {
                printf("Error: Division by zero\n");
                return false;
            }
            factor1 /= factor2;
        }

        skipWhitespace(input, pos);
    }

    *result = factor1;
    return true;
}

// Recursive Descent Parsing for factors (numbers or parentheses)
bool parseFactor(const char *input, int *pos, int *result) {
    skipWhitespace(input, pos);

    if (input[*pos] == '(') {
        (*pos)++;
        if (!parseExpression(input, pos, result)) {
            return false;
        }

        skipWhitespace(input, pos);

        if (input[*pos] == ')') {
            (*pos)++;
            return true;
        } else {
            printf("Error: Missing closing parenthesis\n");
            return false;
        }
    } else if (isdigit(input[*pos])) {
        int num = 0;
        while (isdigit(input[*pos])) {
            num = num * 10 + (input[*pos] - '0');
            (*pos)++;
        }
        *result = num;
        return true;
    } else {
        printf("Error: Invalid factor\n");
        return false;
    }
}

int main() {
    const char *input = "2 + 3 * (4 - 1)";

    int pos = 0;
    int result;

    if (parseExpression(input, &pos, &result) && input[pos] == '\0') {
        printf("Result: %d\n", result);
    } else {
        printf("Error: Invalid expression\n");
    }

    return 0;
}
