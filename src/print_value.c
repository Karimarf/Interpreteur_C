#include <print_value.h>
#include <assign.h>
#include <ast_builder.h>
#include <lexer.h>
#include <my_parser.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_value(Token* tokens) {
    Token* expression_tokens = malloc(255 * sizeof(Token));
    int token_count = 0;
    int i = 0;
    int parentheses_level = 0;
    int inside_parentheses = 0;

    while (tokens[i].type != TOKEN_EOF) {
        if (tokens[i].type == TOKEN_IDENTIFIER && strcmp(tokens[i].value, "print") == 0) {
            i++;
            continue;
        }

        if (tokens[i].type == TOKEN_FONCTION) {
            i++;
            if (tokens[i].type == TOKEN_OPAREN) {
                parentheses_level++;
                i++;
            }
            continue;
        }

        if (tokens[i].type == TOKEN_OPAREN) {
            parentheses_level++;
            inside_parentheses = 1;
            expression_tokens[token_count++] = tokens[i];
            i++;
            continue;
        }

        if (tokens[i].type == TOKEN_CPAREN) {
            if (parentheses_level > 1) {
                expression_tokens[token_count++] = tokens[i];
            }
            parentheses_level--;
            if (parentheses_level == 0) {
                inside_parentheses = 0;
            }
            i++;
            continue;
        }

        if (inside_parentheses || parentheses_level > 0) {
            expression_tokens[token_count++] = tokens[i];
        }

        i++;
    }

    expression_tokens[token_count] = *create_token(TOKEN_EOF, "EOF");

    for (int i = 0; i < token_count; i++) {
        if (expression_tokens[i].type == TOKEN_IDENTIFIER) {
            if (check_if_defined(expression_tokens[i].value) == 0) {
                printf("Erreur : La variable '%s' n'est pas definie.\n", expression_tokens[i].value);
                free(expression_tokens);
                exit(EXIT_FAILURE);
            }
        }
    }

    for (int i = 0; i < token_count; i++) {
        if (expression_tokens[i].type == TOKEN_IDENTIFIER) {
            int value = recher(expression_tokens[i].value);
            if (value == 0) {
                printf("Erreur  : La variable '%s' n'est pas definie.\n", expression_tokens[i].value);
                free(expression_tokens);
                exit(EXIT_FAILURE);
            }
            char value_str[20];
            snprintf(value_str, sizeof(value_str), "%d", value);

            expression_tokens[i] = *create_token(TOKEN_NUMBER, value_str);
        }
    }

    Token* postfix_tokens = shunting_yard(expression_tokens);

    Node* ast_root = create_ast(postfix_tokens);
    int result_value = evaluate(ast_root);

    printf("%d\n",result_value);


    free(expression_tokens);
    free(postfix_tokens);
    freeAST(ast_root);

}
