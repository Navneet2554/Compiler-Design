#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Define token types
#define KEYWORD 1
#define IDENTIFIER 2
#define OPERATOR 3
#define LITERAL 4 //Constant 
#define SYMBOL 5 //Special character

// Function to check if a word is a keyword
int is_keyword(char *word) {
    char *keywords[] = {"if", "else", "for", "while", "do", "switch", "case", "default", "break", "continue", "return", "int", "float", "char", "double", "void"};
    int i;
    for (i = 0; i < 16; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is an operator
int is_operator(char c) {
    char operators[] = {'+', '-', '*', '/', '%', '=', '<', '>', '!'};
    int i;
    for (i = 0; i < 9; i++) {
        if (c == operators[i]) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is a symbol
int is_symbol(char c) {
    char symbols[] = {'(', ')', '[', ']', '{', '}', ',', ';', ':'};
    int i;
    for (i = 0; i < 9; i++) {
        if (c == symbols[i]) {
            return 1;
        }
    }
    return 0;
}

// Function to tokenize the input program
void tokenize(char *program) {
    int i, j;
    char word[100];
    int token_count = 0;

    printf("Lexeme\tToken Name\tToken\n");
    printf("----------------------------------------\n");

    for (i = 0; program[i] != '\0'; i++) {
        // Skip whitespace
        if (isspace(program[i])) {
            continue;
        }

        // Check for keywords and identifiers
        if (isalpha(program[i])) {
            j = 0;
            while (isalnum(program[i])) {
                word[j++] = program[i++];
            }
            word[j] = '\0';
            i--;

            if (is_keyword(word)) {
                printf("%s\tKeyword\t\t%d\n", word, KEYWORD);
            } else {
                printf("%s\tIdentifier\t%d\n", word, IDENTIFIER);
            }
            token_count++;
        }

        // Check for operators
        else if (is_operator(program[i])) {
            printf("%c\tOperator\t%d\n", program[i], OPERATOR);
            token_count++;
        }

        // Check for literals
        else if (isdigit(program[i])) {
            j = 0;
            while (isdigit(program[i])) {
                word[j++] = program[i++];
            }
            word[j] = '\0';
            i--;

            printf("%s\tLiteral\t\t%d\n", word, LITERAL);
            token_count++;
        }

        // Check for symbols
        else if (is_symbol(program[i])) {
            printf("%c\tSymbol\t\t%d\n", program[i], SYMBOL);
            token_count++;
        }
    }

    printf("\nTotal number of tokens: %d\n", token_count);
}

int main() {
    char program[1000];
    printf("Enter a program: ");
    fgets(program, sizeof(program), stdin);
    tokenize(program);
    return 0;
}