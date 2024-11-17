#include "../include/interpret.h"
#include "../include/lexer.h"
#include "../include/my_parser.h"
#include <stdio.h>
#include <stdlib.h>

void interpret(Token* tokens) {
    Token* expression_tokens = NULL;

    if (tokens[0].type == TOKEN_FONCTION) {
        expression_tokens = expression_in_fonction_tokens(tokens);
    } else if (tokens[0].type == TOKEN_IDENTIFIER) {
        expression_tokens = expression_in_identifier(tokens);
    } else if (tokens[0].type == TOKEN_TYPE && tokens[2].type == TOKEN_ASSIGN) {
        expression_tokens = expression_new_identifier(tokens);
    } else {
        printf("Expression non reconnue.\n");
        free(tokens);
    }

}
