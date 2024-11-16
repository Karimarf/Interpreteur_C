#include "../include/interactive_mode.h"
#include "../include/assign.h"
#include "../include/error.h"
#include "../include/lexer.h"
#include "../include/interpret.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int interactive_mode() {
    NodeList* var_list = NULL;
    printf("> Mode interactif");
    printf("\nEntrez une expression (ou tapez 0 pour quitter): \n");
    while (1) {
        char input[256];
        fgets(input, 256, stdin);

        if (strcmp(input, "0\n") == 0) {
            printf("Sortie du mode interactif.\n");
            break;
        }

        Token* tokens = lexer(input);
        Token* errors = inputs_error(tokens);
        interpret(tokens);

        free(tokens);

    }
    return 0;

}



