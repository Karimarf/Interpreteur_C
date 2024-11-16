#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/my_parser.h"
#include "../include/assign.h"
#include "../include/lexer.h"
#include "../include/ast_builder.h"
#include "../include/print_value.h"



Token* expression_in_fonction_tokens(Token* tokens) {

    if(tokens[0].type == TOKEN_FONCTION && strcmp(tokens[0].value, "print") == 0) {
        print_value(tokens);

    }

}

Token* expression_in_identifier(Token* tokens) {
    int token_count = 0;

    for (int i = 2; tokens[i].type != TOKEN_EOF && tokens[i].type != TOKEN_SEMICOLON; i++) {
        token_count++;
    }
    Token* expression_tokens = malloc((token_count + 1) * sizeof(Token));
    int j = 0;
    for (int i = 2; tokens[i].type != TOKEN_EOF && tokens[i].type != TOKEN_SEMICOLON; i++) {
        expression_tokens[j++] = tokens[i];
    }
    expression_tokens[j] = *create_token(TOKEN_EOF, "EOF");

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

    const char* var_name = tokens[0].value;

    if (check_if_defined(var_name) == 0) {
        free(expression_tokens);
        free(postfix_tokens);
        printf("Erreur  : La variable '%s' n'est pas definie.\n", var_name);
        exit(EXIT_FAILURE);
    }

    modif(var_name, result_value);


    free(var_name);
    free(expression_tokens);
    free(postfix_tokens);
    freeAST(ast_root);
}



Token* expression_new_identifier(Token* tokens) {

    int token_count = 0;
    for (int i = 2; tokens[i].type != TOKEN_EOF; i++) {
        if (tokens[i].type != TOKEN_ASSIGN && tokens[i].type != TOKEN_SEMICOLON) {
            token_count++;
        }
    }

    Token* expression_tokens = malloc((token_count + 1) * sizeof(Token));
    int j = 0;
    for (int i = 2; tokens[i].type != TOKEN_EOF; i++) {
        if (tokens[i].type != TOKEN_ASSIGN && tokens[i].type != TOKEN_SEMICOLON) {
            expression_tokens[j++] = tokens[i];
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

    expression_tokens[j] = *create_token(TOKEN_EOF, "EOF");

    Token* postfix_tokens = shunting_yard(expression_tokens);

    Node* ast_root = create_ast(postfix_tokens);

    int result_value = evaluate(ast_root);

    const char* var_name = tokens[1].value;
    ajout(var_name, result_value);


    free(var_name);
    free(expression_tokens);
    free(postfix_tokens);
    freeAST(ast_root);

}



int prio(char operator) {
    if (operator == '+' || operator == '-') {
        return 1;
    }
    if (operator == '*' || operator == '/') {
        return 2;
    }
    return 0;
}


Token* shunting_yard(Token* tokens) {
    Token* output_tokens = malloc(255 * sizeof(Token));
    char operators[255] = {0};
    int output_i = 0;
    int operators_i = 0;

    for (int i = 0; tokens[i].type != TOKEN_EOF; i++) {
        if (tokens[i].type == TOKEN_IDENTIFIER || tokens[i].type == TOKEN_NUMBER) {
            output_tokens[output_i++] = *create_token(tokens[i].type, tokens[i].value);
        }
        else if (tokens[i].type == TOKEN_OPAREN) {
            operators[operators_i++] = tokens[i].value[0];
        }
        else if (tokens[i].type == TOKEN_CPAREN) {
            while (operators_i > 0 && operators[operators_i - 1] != '(') {
                char op[2] = {operators[--operators_i], '\0'};
                output_tokens[output_i++] = *create_token(TOKEN_OPERATOR, op);
            }
            operators_i--;
        }
        else if (tokens[i].type == TOKEN_OPERATOR) {
            while (operators_i > 0 && prio(operators[operators_i - 1]) >= prio(tokens[i].value[0])) {
                char op[2] = {operators[--operators_i], '\0'};
                output_tokens[output_i++] = *create_token(TOKEN_OPERATOR, op);
            }
            operators[operators_i++] = tokens[i].value[0];
        }
    }

    while (operators_i > 0) {
        char op[2] = {operators[--operators_i], '\0'};
        output_tokens[output_i++] = *create_token(TOKEN_OPERATOR, op);
    }

    output_tokens[output_i++] = *create_token(TOKEN_EOF, "EOF");

    return output_tokens;
}
