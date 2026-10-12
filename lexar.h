#ifndef LEXAR_H
#define LEXAR_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/* Token types */
typedef enum
{
    KEYWORD,
    IDENTIFIER,
    INTEGER_CONSTANT,
    FLOATING_CONSTANT,
    CHARACTER_CONSTANT,
    STRING_LITERAL,
    OPERATOR,
    SPECIAL_SYMBOL,
    PREPROCESSOR_DIRECTIVE,
    INVALID
} TokenType;

/* Token structure */
typedef struct
{
    char lexeme[100];
    TokenType type;
}Token;

/* Function prototypes */
int is_keyword(char *word);
void print_token(Token tokens);
void add_token(Token tokens[], int *count, char *lexeme, TokenType type);
void analyze_file(FILE *fp);

#endif
