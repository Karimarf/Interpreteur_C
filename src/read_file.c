#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/assign.h"
#include "../include/lexer.h"
#include "../include/interpret.h"
#include "../include/error.h"
#include "../include/read_file.h"

int read_files(const char* input) {
    int i = 0;
    if(input == NULL || input[0] == '\0') {
        fprintf(stderr,"Le chemin est vide \n");
        exit(EXIT_FAILURE);
    }

    FILE* file = fopen(input, "r");

    if(file == NULL) {
        fprintf(stderr,"Fichier non trouve pour '%s'\n", input);
        exit(EXIT_FAILURE);
    }
    printf("Fichier trouve pour '%s'\n", input);
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Token* tokens = lexer(line);
        Token* errors = inputs_error(tokens);

        interpret(tokens);
        free(tokens);

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


