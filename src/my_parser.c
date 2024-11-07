#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/assign.h"
#include "../include/lexer.h"
#include "../include/my_parser.h"
#include "../include/ast_builder.h"
#include "../include/error.h"


Token* expression_in_fonction_tokens(Token* tokens) {
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
    return expression_tokens;
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

    Token* postfix_tokens = shunting_yard(expression_tokens);

    Node* ast_root = create_ast(postfix_tokens);

    int result_value = evaluate(ast_root);

    const char* var_name = tokens[0].value;

    if (print_v(var_name) == 0) {
        free(expression_tokens);
        free(postfix_tokens);
        printf("Erreur  : La variable '%s' n'est pas definie.\n", var_name);
        exit(EXIT_FAILURE);
    }

    modif(var_name, result_value);

    int test = recher(var_name);
    printf("test = %d\n", test);

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
    expression_tokens[j] = *create_token(TOKEN_EOF, "EOF");

    Token* postfix_tokens = shunting_yard(expression_tokens);

    Node* ast_root = create_ast(postfix_tokens);

    int result_value = evaluate(ast_root);

    const char* var_name = tokens[1].value;
    ajout(var_name, result_value);

    int test = recher(var_name);
    printf("test = %d\n", test);

    free(var_name);
    free(expression_tokens);
    free(postfix_tokens);
    freeAST(ast_root);

}



Token* expression_edit_value(Token* tokens) {
    int token_count = 0;
    for (int i = 1; tokens[i].type != TOKEN_EOF; i++) {
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
    expression_tokens[j] = *create_token(TOKEN_EOF, "EOF");
    return expression_tokens;
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
