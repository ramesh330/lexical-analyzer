#include "lexar.h"

int is_keyword(char *word)
{
    char *keywords[] = {
        "auto", "break", "case", "char", "const",
        "continue", "default", "do", "double", "else",
        "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return",
        "short", "signed", "sizeof", "static", "struct",
        "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while"
    };

    int count = sizeof(keywords) / sizeof(keywords[0]);

    for(int i=0; i<count; i++)
    {
        if(strcmp(word,keywords[i])==0)
        return 1;
    }
    return 0;
}

void print_token(Token token)
{
    printf("%-30s ", token.lexeme);

    switch (token.type)
    {
        case KEYWORD:
            printf("KEYWORD\n");
            break;

        case IDENTIFIER:
            printf("IDENTIFIER\n");
            break;

        case INTEGER_CONSTANT:
            printf("INTEGER_CONSTANT\n");
            break;

        case FLOATING_CONSTANT:
            printf("FLOATING_CONSTANT\n");
            break;

        case CHARACTER_CONSTANT:
            printf("CHARACTER_CONSTANT\n");
            break;

        case STRING_LITERAL:
            printf("STRING_LITERAL\n");
            break;

        case OPERATOR:
            printf("OPERATOR\n");
            break;

        case SPECIAL_SYMBOL:
            printf("SPECIAL_SYMBOL\n");
            break;

        case PREPROCESSOR_DIRECTIVE:
            printf("PREPROCESSOR_DIRECTIVE\n");
            break;

        case INVALID:
            printf("INVALID\n");
            break;
    }
}

void add_token(Token tokens[], int *count, char *lexeme, TokenType type)
{
    if (*count >= 1000)
    {
        printf("Error: Maximum token limit reached\n");
        return;
    }

    strcpy(tokens[*count].lexeme, lexeme);
    tokens[*count].type = type;
    (*count)++;
}

void analyze_file(FILE *fp)
{
    Token tokens[1000];
    int token_count = 0;
    int line_number = 1;
    int ch;

    printf("%-30s %s\n","LEXEME","TOKEN TYPE");
    printf("----------------------------------------------------------\n");
    while ((ch = fgetc(fp)) != EOF)
    {
        /* Handle whitespace */
        if (ch == '\n')
        {
            line_number++;
            continue;
        }

        if (isspace(ch))
        {
            continue;
        }

        /* Identifier / Keyword */
        if (isalpha(ch) || ch == '_')
        {
            char lexme[100];
            int i = 0;

            while (isalpha(ch) || isdigit(ch) || ch == '_')
            {
                lexme[i++] = ch;
                ch = fgetc(fp);
            }

            lexme[i] = '\0';

            if (is_keyword(lexme))
                add_token(tokens, &token_count, lexme, KEYWORD);
            else
                add_token(tokens, &token_count, lexme, IDENTIFIER);

            ungetc(ch, fp);
        }

        /* Integer Constant */
        else if (isdigit(ch))
        {
            char lexeme[100];
            int i = 0;
            int flag = 0;

            while (isdigit(ch) || ch == '.')
            {
                if (ch == '.')
                {
                    flag++;

                    if (flag > 1)
                    {
                        lexeme[i++] = ch;
                        ch = fgetc(fp);

                        while (isdigit(ch) || ch == '.')
                        {
                            lexeme[i++] = ch;
                            ch = fgetc(fp);
                        }

                        lexeme[i] = '\0';

                        add_token(tokens, &token_count, lexeme, INVALID);

                        if (ch != EOF)
                            ungetc(ch, fp);

                        break;
                    }
                }

                lexeme[i++] = ch;
                ch = fgetc(fp);
            }

            if (flag <= 1)
            {
                lexeme[i] = '\0';

                /* Number followed by alphabetic character */
                if (isalpha(ch) || ch == '_')
                {
                    while (isalnum(ch) || ch == '_')
                    {
                        lexeme[i++] = ch;
                        ch = fgetc(fp);
                    }

                    lexeme[i] = '\0';

                    add_token(tokens, &token_count, lexeme, INVALID);

                    if (ch != EOF)
                        ungetc(ch, fp);
                }
                else
                {
                    if (flag == 1)
                    {
                        if (lexeme[i - 1] == '.')
                            add_token(tokens, &token_count, lexeme, INVALID);
                        else
                            add_token(tokens, &token_count, lexeme, FLOATING_CONSTANT);
                    }
                    else
                        add_token(tokens, &token_count, lexeme, INTEGER_CONSTANT);

                    if (ch != EOF)
                        ungetc(ch, fp);
                }
            }
        }

        /* string literal */
        else if (ch == '"')
        {
            char lexeme[100];
            int i = 0;
            int closed = 0;

            lexeme[i++] = ch;

            ch = fgetc(fp);

            while (ch != EOF && ch != '\n')
            {
                if (ch == '\\')
                {
                    lexeme[i++] = ch;

                    ch = fgetc(fp);

                    if (ch != EOF)
                    {
                        lexeme[i++] = ch;
                        ch = fgetc(fp);
                    }

                    continue;
                }

                lexeme[i++] = ch;

                if (ch == '"')
                {
                    closed = 1;
                    break;
                }

                ch = fgetc(fp);
            }

            lexeme[i] = '\0';

            if (closed)
            {
                add_token(tokens, &token_count, lexeme, STRING_LITERAL);
            }
            else
            {
                printf("Lexical Error at line %d: Unterminated string literal\n",
                    line_number - 1);

                if (ch == '\n')
                {
                    line_number++;
                }

                add_token(tokens, &token_count, lexeme, INVALID);
            }
        }

        /* character constant */
        else if (ch == '\'')
        {
            char lexeme[10];
            int i = 0;
            int valid = 0;

            lexeme[i++] = ch;

            ch = fgetc(fp);

            /* Escape sequence */
            if (ch == '\\')
            {
                lexeme[i++] = ch;

                ch = fgetc(fp);

                if (ch == 'n' || ch == 't' ||
                    ch == 'r' || ch == '\\' ||
                    ch == '\'' || ch == '\"' ||
                    ch == '0')
                {
                    lexeme[i++] = ch;
                    valid = 1;
                }
                else
                {
                    lexeme[i++] = ch;
                }
            }
            else if (ch != '\'' && ch != '\n' && ch != EOF)
            {
                /* Normal character */
                lexeme[i++] = ch;
                valid = 1;
            }

            ch = fgetc(fp);

            if (ch == '\'')
            {
                lexeme[i++] = ch;
            }
            else
            {
                valid = 0;

                while (ch != '\'' && ch != '\n' && ch != EOF)
                {
                    lexeme[i++] = ch;
                    ch = fgetc(fp);
                }

                if (ch == '\'')
                {
                    lexeme[i++] = ch;
                }
            }

            lexeme[i] = '\0';

            if (valid)
            {
                add_token(tokens, &token_count, lexeme, CHARACTER_CONSTANT);
            }
            else
            {
                printf("Lexical Error at line %d: Invalid character constant '%s'\n",
                    line_number, lexeme);
                add_token(tokens, &token_count, lexeme, INVALID);
            }
        }

        /* Operators */
        else if (ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == '%' || ch == '=' ||
            ch == '<' || ch == '>' || ch == '!' ||
            ch == '&' || ch == '|')
        {
            int next = fgetc(fp);

            /* Single-line comment */
            if(ch == '/' && next == '/')
            {
                while(ch != '\n' && ch != EOF)
                {
                    ch = fgetc(fp);
                }

                if(ch == '\n')
                {
                    line_number++;
                }

                continue;
            }

            /* Multi-line comment */
            if(ch == '/' && next == '*')
            {
                int closed = 0;

                while(1)
                {
                    ch = fgetc(fp);

                    if(ch == EOF)
                        break;

                    if(ch == '\n')
                    {
                        line_number++;
                    }

                    if(ch == '*')
                    {
                        next = fgetc(fp);

                        if(next == '/')
                        {
                            closed = 1;
                            break;
                        }
                        else if(next != EOF)
                        {
                            ungetc(next, fp);
                        }
                    }
                }

                if(!closed)
                {
                    printf("Lexical Error at line %d: Unterminated comment\n",
                        line_number);
                }

                continue;
            }

            if ((ch == '+' && (next == '+' || next == '=')) ||
                (ch == '-' && (next == '-' || next == '=')) ||
                (ch == '*' && next == '=') ||
                (ch == '/' && next == '=') ||
                (ch == '%' && next == '=') ||
                (ch == '=' && next == '=') ||
                (ch == '!' && next == '=') ||
                (ch == '<' && next == '=') ||
                (ch == '>' && next == '=') ||
                (ch == '&' && next == '&') ||
                (ch == '|' && next == '|'))
            {
                char lexme[3];
                lexme[0] = ch;
                lexme[1] = next;
                lexme[2] = '\0';
                add_token(tokens, &token_count, lexme, OPERATOR);

            }
            else
            {
                char lexme[2];
                lexme[0] = ch;
                lexme[1] ='\0';
                add_token(tokens, &token_count, lexme, OPERATOR);
                ungetc(next, fp);
            }
        }

        /* Special Symbols */
        else if (ch == '(' || ch == ')' ||
            ch == '{' || ch == '}' ||
            ch == '[' || ch == ']' ||
            ch == ';' || ch == ',' ||
            ch == ':')
        {
            char lexme[2];
            lexme[0] = ch;
            lexme[1] ='\0';
            add_token(tokens, &token_count, lexme, SPECIAL_SYMBOL);
        }

        else if (ch == '.')
        {
            char lexeme[100];
            int i = 0;

            lexeme[i++] = ch;

            ch = fgetc(fp);

            if (isdigit(ch))
            {
                while (isdigit(ch))
                {
                    lexeme[i++] = ch;
                    ch = fgetc(fp);
                }

                lexeme[i] = '\0';

                printf("Lexical Error at line %d: Invalid number '%s'\n",
                    line_number, lexeme);

                add_token(tokens, &token_count, lexeme, INVALID);

                if (ch != EOF)
                    ungetc(ch, fp);
            }
            else
            {
                lexeme[i] = '\0';

                add_token(tokens, &token_count, lexeme, SPECIAL_SYMBOL);

                if (ch != EOF)
                    ungetc(ch, fp);
            }
        }

        /* preprocessing directive */
        else if (ch == '#')
        {
            char lexme[100];
            int i = 0;
            lexme[i++] = ch;
            ch = fgetc(fp);

            while (ch != '\n' && ch != EOF)
            {
                lexme[i++] = ch;
                ch = fgetc(fp);
            }

            lexme[i] = '\0';
            if(ch == '\n')
            {
                line_number++;
            }
            add_token(tokens, &token_count,lexme,PREPROCESSOR_DIRECTIVE);

        }

        else
        {
            char lexeme[2];

            lexeme[0] = ch;
            lexeme[1] = '\0';

            printf("Lexical Error at line %d: Invalid character '%c'\n",
                line_number, ch);

            add_token(tokens, &token_count, lexeme, INVALID);
        }
    }

    for (int i = 0; i < token_count; i++)
    {
        print_token(tokens[i]);
    }
}