#ifndef PARSER_H
#define PARSER_H


#include "lexer.h"


Token* expression_in_fonction_tokens(Token* tokens);
Token* expression_in_identifier(Token* tokens);
Token* expression_new_identifier(Token* tokens);
Token* expression_edit_value(Token* tokens);
Token* shunting_yard(Token* tokens);


#endif
