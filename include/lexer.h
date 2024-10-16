#ifndef LEXER_H
#define LEXER_H


typedef enum {
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_OPERATOR,
    TOKEN_QUOT,
    TOKEN_ASSIGN,
    TOKEN_OPAREN,
    TOKEN_CPAREN,
    TOKEN_SEMICOLON,
    TOKEN_TYPE,
    TOKEN_FONCTION,
    TOKEN_EOF,
} TokenType;

typedef struct {
    TokenType type;
    char* value;
} Token;

Token* lexer(const char* input);
Token* create_token(TokenType type, const char* value);
void free_tokens(Token* tokens);
int is_number(char c);
int is_letter(char c);
int is_operator(char c);

#endif
