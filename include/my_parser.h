#ifndef PARSER_H
#define PARSER_H

#include "..\include\lexer.h"


extern Token* expression_in_fonction_tokens(Token* tokens) ;
extern  Token* expression_in_identifier(Token* tokens);
extern  Token* expression_new_identifier(Token* tokens);
extern  Token* expression_edit_value(Token* tokens);
extern  Token* shunting_yard(Token* tokens);


#endif
