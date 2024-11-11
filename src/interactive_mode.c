#include <interactive_mode.h>
#include <assign.h>
#include <error.h>
#include <lexer.h>
#include <my_parser.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Token * inputs_error(Token * token);

int interactive_mode() {
    NodeList* var_list = NULL;
    printf("> Mode interactif");
    printf("\nEntrez une expression (ou tapez 0 pour quitter): \n");
    while (1) {
        char input[256];
        fgets(input, 256, stdin);

        if (strcmp(input, "0\n") == 0) {
            printf("Sortie du mode interactif.\n");
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



