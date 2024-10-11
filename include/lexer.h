#ifndef LEXER_H
#define LEXER_H


typedef enum {
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_OPERATOR,
    TOKEN_ASSIGN,
    TOKEN_OPAREN,
    TOKEN_CPAREN,
    TOKEN_SEMICOLON,
    TOKEN_TYPE,
    TOKEN_FONCTION,
    TOKEN_EOF,
    TOKEN_ERROR,
} TokenType;

typedef struct {
    TokenType type;
    char* value;
} Token;

extern Token* lexer(const char* input);
extern Token* create_token(TokenType type, const char* value);
extern void free_tokens(Token* tokens);
extern int is_number(char c);
extern int is_letter(char c);
extern int is_operator(char c);

#endif
