#include <stdlib.h>
#include <string.h>
#include "..\include\lexer.h"

Token* create_token(TokenType type, const char* value) {
    Token* token = malloc(sizeof(Token));
    token->type = type;
    token->value = malloc(strlen(value) + 1);
    strcpy(token->value, value);
    return token;
}

int is_number(char c) {
    return (c >= '0' && c <= '9');
}

int is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c=='%');
}

void free_tokens(Token* tokens) {
    int i = 0;
    while (tokens[i].type != TOKEN_EOF) {
        free(tokens[i].value);
        i++;
    }
    free(tokens);
}

Token* lexer(const char* input) {
    Token* tokens = malloc(255 * sizeof(Token));
    int token_count = 0;
    int i = 0;

    while (input[i] != '\0' ) {

        if (input[i] == 32 ) {
            i++;
            continue;
        }

        if (is_number(input[i])) {
            int start = i;
            while (is_number(input[i])) i++;
            char* number = malloc((i - start + 1) * sizeof(char));
            strncpy(number, &input[start], i - start);
            number[i - start] = '\0';
            tokens[token_count++] = *create_token(TOKEN_NUMBER, number);
            free(number);
        }

        if (is_letter(input[i])) {
            int start = i;
            while (is_letter(input[i])) i++;
            char* identifier = malloc((i - start + 1) * sizeof(char));
            strncpy(identifier, &input[start], i - start);
            identifier[i - start] = '\0';

            if (strcmp(identifier, "print") == 0) { // Correct
                tokens[token_count++] = *create_token(TOKEN_FONCTION, identifier);
            } else if (strcmp(identifier, "int") == 0 || strcmp(identifier, "char") == 0 || strcmp(identifier, "float") == 0) {
                tokens[token_count++] = *create_token(TOKEN_TYPE, identifier);
            } else {
                tokens[token_count++] = *create_token(TOKEN_IDENTIFIER, identifier);
            }

            free(identifier);
        }

        if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
            char op[2] = {input[i], '\0'};
            tokens[token_count++] = *create_token(TOKEN_OPERATOR, op);
            i++;
            continue;
        }
        if (input[i] == '=') {
            tokens[token_count++] = *create_token(TOKEN_ASSIGN, "=");
            i++;
            continue;
        }
        if (input[i] == '(') {
            tokens[token_count++] = *create_token(TOKEN_OPAREN, "(");
            i++;
            continue;
        }
        if (input[i] == ')') {
            tokens[token_count++] = *create_token(TOKEN_CPAREN, ")");
            i++;
            continue;
        }
        if (input[i] == ';') {
            tokens[token_count++] = *create_token(TOKEN_SEMICOLON, ";");
            break;
        }
        i++;
    }
    tokens[token_count++] = *create_token(TOKEN_EOF, "EOF");
    return tokens;
}
