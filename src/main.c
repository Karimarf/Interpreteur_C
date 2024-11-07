#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/assign.h"
#include "../include/lexer.h"
#include "../include/my_parser.h"
#include "../include/ast_builder.h"
#include "../include/error.h"


Token * inputs_error(Token * token);

int main()
{
    char input[256];
    NodeList* var_list = NULL;
    while (1) {
        printf("\nEntrez une expression (ou tapez 0 pour quitter): \n");
        fgets(input, 256, stdin);

        if (strcmp(input, "0\n") == 0) {
            printf("Sortie du programme.\n");
            break;
        }

        Token* tokens = lexer(input);
        Token* errors = inputs_error(tokens);
        Token* expression_tokens;

        if (tokens[0].type == TOKEN_FONCTION) {
            expression_tokens = expression_in_fonction_tokens(tokens);
            continue;
        } else if (tokens[0].type == TOKEN_IDENTIFIER) {
            expression_tokens = expression_in_identifier(tokens);
            continue;
        } else if (tokens[0].type == TOKEN_TYPE && tokens[2].type == TOKEN_ASSIGN) {
            expression_tokens = expression_new_identifier(tokens);
            continue;
        } else {
            printf("Expression non reconnue.\n");
            free(tokens);
            continue;
        }

        free(tokens);
        free(expression_tokens);
    }
    return 0;
}
