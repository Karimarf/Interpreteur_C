#include <read_file.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assign.h>
#include <lexer.h>
#include <my_parser.h>
#include <error.h>

int read_files(const char* input) {
    int i = 0;
    if(input == NULL || input[0] == '\0') {
        fprintf(stderr,"Le chemin est vide \n");
        exit(EXIT_FAILURE);
    }

    FILE* file = fopen(input, "r");

    if(file == NULL) {
        fprintf(stderr,"Fichier non trouvé pour '%s'\n", input);
        exit(EXIT_FAILURE);
    }
    printf("Fichier trouvé pour '%s'\n", input);
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Token* tokens = lexer(line);
        Token* errors = inputs_error(tokens);
        Token* expression_tokens;

        if (tokens[0].type == TOKEN_FONCTION) {
            expression_tokens = expression_in_fonction_tokens(tokens);
            continue;
        } else if (tokens[0].type == TOKEN_IDENTIFIER) {
            expression_tokens = expression_in_identifier(tokens);
            continue;
        } else if (tokens[0].type == TOKEN_TYPE && tokens[2].type == TOKEN_ASSIGN) {
            expression_tokens = expression_new_identifier(tokens);
            continue;
        } else {
            fprintf(stderr, "Expression non reconnue.\n");
            free(tokens);
            continue;
        }
        free(tokens);
        free(expression_tokens);
    }
    fclose(file);
    return 0;
}

int read_file_mode() {
    NodeList* var_list = NULL;
    while (1) {
        char input[256];
        printf("\nEntrez le chemin du fichier a lire (ou tapez 0 pour quitter): \n");
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (strcmp(input, "0\n") == 0) {
                printf("Sortie du mode lecture de fichier.\n");
                return 0;
            }
            size_t length = strlen(input);
            if (length > 0 && input[length - 1] == '\n') {
                input[length - 1] = '\0';
            }
            read_files(input);
        }

    }
}


