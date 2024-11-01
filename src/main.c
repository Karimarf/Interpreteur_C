#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lexer.h"
#include "../include/assign.h"
#include "../include/my_parser.h"
#include "../include/ast_builder.h"
#include "assign.h"
#include "../include/error.h"



int main()
{
    char input[256];

    while (1) {
        printf("Entrez une expression (ou tapez 0 pour quitter): ");
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
        } else if (tokens[0].type == TOKEN_TYPE && strcmp(tokens[0].value, "char") == 0) {
            continue;
        } else if (tokens[0].type == TOKEN_IDENTIFIER) {
            expression_tokens = expression_in_identifier(tokens);
        } else if (tokens[0].type == TOKEN_TYPE && tokens[2].type == TOKEN_ASSIGN) {
            expression_tokens = expression_new_identifier(tokens);
        } else if (tokens[0].type == TOKEN_IDENTIFIER && tokens[1].type == TOKEN_ASSIGN) {
            expression_tokens = expression_edit_value(tokens);
        } else {
            printf("Expression non reconnue.\n");
            free(tokens);
            continue;
        }

        printf("//////////////////////////////////\n");
    if (tokens[0].type == TOKEN_FONCTION) {
        expression_tokens = expression_in_fonction_tokens(tokens);
    } else if (tokens[0].type == TOKEN_TYPE && strcmp(tokens[0].value, "char") == 0) {
    }
    else if (tokens[0].type == TOKEN_IDENTIFIER) {
        expression_tokens = expression_in_identifier(tokens);
    }
    else if (tokens[0].type == TOKEN_TYPE && tokens[2].type == TOKEN_ASSIGN) {
        expression_tokens = expression_new_identifier(tokens);
    } else if (tokens[0].type == TOKEN_IDENTIFIER && tokens[1].type == TOKEN_ASSIGN) {
        expression_tokens = expression_edit_value(tokens);
    }

    Token* assignment_token = expression_assign(tokens);
    Token* Shunting_Yard_expression = shunting_yard(expression_tokens);
    printf("////////////////////////////////\n");


    for (int i = 0; Shunting_Yard_expression[i].type != TOKEN_EOF; i++) {
        printf("%s", Shunting_Yard_expression[i].value);
    }


    printf("\n\n");

    if(assignment_token[0].type == TOKEN_IDENTIFIER && assignment_token[1].type == TOKEN_ASSIGN)
    {
        printf("\n ASSIGN \n");
        assign(assignment_token);
    }
    else if (assignment_token[0].type == TOKEN_FONCTION)
    {
        printf("\n PRINT \n");
        printf("%d \n",print_v(assignment_token));
    }
    else
    {
        Node* ast = create_ast(Shunting_Yard_expression);
        printf("\nPRINT AST\n");
        printAst(ast);

        printf("\nEVALUATE AST\n");
        int result  = evaluate(ast);
        printf("\nRESULT: %d\n", result);

        free(tokens);
        free(Shunting_Yard_expression);
        free(expression_tokens);
    }
        freeAST(ast);
    }
    return 0;
}
