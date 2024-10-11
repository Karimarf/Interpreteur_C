#include <stdio.h>
#include <stdlib.h>
#include "..\include\lexer.h"
#include "..\include\my_parser.h"

int main() {
    char input[256];
    fgets(input, 256, stdin);

    Token* tokens = lexer(input);



    Token* expression_tokens;

    if (tokens[0].type == TOKEN_FONCTION) {
        expression_tokens = expression_in_fonction_tokens(tokens);
    } else if (tokens[0].type == TOKEN_TYPE && tokens[2].type == TOKEN_ASSIGN) {
        expression_tokens = expression_new_identifier(tokens);
    } else if (tokens[0].type == TOKEN_IDENTIFIER && tokens[1].type == TOKEN_ASSIGN) {
        expression_tokens = expression_edit_value(tokens);
    }


    printf("//////////////////////////////////\n");

    Token* Shunting_Yard_expression = shunting_yard(expression_tokens);


    printf("////////////////////////////////\n");
    for (int i = 0; Shunting_Yard_expression[i].type != TOKEN_EOF; i++) {
        printf("%s ", Shunting_Yard_expression[i].value);
    }
    printf("\n");

    free(tokens);
    free(expression_tokens);

    return 0;
}