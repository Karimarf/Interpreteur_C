#include <stdio.h>
#include <stdlib.h>
#include "../include/lexer.h"
#include "../include/my_parser.h"
#include "../include/ast_builder.h"

int main() {
    char input[256] = "103 + 4 * (2 - 1)";
    //fgets(input, 256, stdin);
    Token* tokens = lexer(input);

    // Affichage des tokens générés pour le débogage
    for (int i = 0; tokens[i].type != TOKEN_EOF; i++) {
        printf("Token[%d]: type=%d, value=%s\n", i, tokens[i].type, tokens[i].value);
    }

    Token* expression_tokens;

    if (tokens[0].type == TOKEN_FONCTION) {
        expression_tokens = expression_in_fonction_tokens(tokens);
    } else if (tokens[0].type == TOKEN_TYPE && tokens[2].type == TOKEN_ASSIGN) {
        expression_tokens = expression_new_identifier(tokens);
    } else if (tokens[0].type == TOKEN_IDENTIFIER && tokens[1].type == TOKEN_ASSIGN) {
        expression_tokens = expression_edit_value(tokens);
    }


    printf("//////////////////////////////////\n");

    Token* Shunting_Yard_expression = shunting_yard(tokens);
    printf("////////////////////////////////\n");
    for (int i = 0; Shunting_Yard_expression[i].type != TOKEN_EOF; i++) {
        printf("%s", Shunting_Yard_expression[i].value);
    }

    Node* ast = create_ast(Shunting_Yard_expression);
    printf("\nPRINT AST\n");
    printAst(ast);

    printf("\nEVALUATE AST\n");
    int result  = evaluate(ast);
    printf("\nRESULT: %d\n", result);

    free(tokens);
    free(expression_tokens);

    return 0;
}