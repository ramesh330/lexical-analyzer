/*
  Name      : Ramesh Pandhare
  Project   : Lexical Analyzer
  Date      : 12/10/26
 
 * Description:

    -A C-based Lexical Analyzer that reads a C source file, identifies

    -and classifies tokens such as keywords, identifiers, constants,

    -strings, operators, special symbols, and preprocessor directives.

    -It also detects and reports common lexical errors with line numbers.
 */


#include "lexar.h"

int main(int argc, char *argv[])
{
    /* Validations */
    if(argc != 2)
    {
        printf("Insufficient arguments\n");
        printf("Uses : <./lexar> <source file>\n");
        return 1;
    }

    char *ptr = strstr(argv[1],".c");
    if(ptr == NULL || strcmp(ptr,".c") != 0)
    {
        printf("Invalid source file\n");
        printf("Uses : <./lexar> <.c file>\n");
        return 1;
    }

    FILE *fp;

    if((fp = fopen(argv[1],"r")) == NULL)
    {
        perror(" ");
        return 1;
    }

    /* Analyze the file */
    analyze_file(fp);

    fclose(fp);

    return 0;
}