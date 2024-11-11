#include <stdio.h>
#include <string.h>
#include <assign.h>
#include <lexer.h>
#include <read_file.h>
#include <interactive_mode.h>


Token * inputs_error(Token * token);

int main()
{
    char input[256];

    NodeList* var_list = NULL;

    while (1) {
        printf("--------- MENU ---------\n");
        printf("1- Mode interactif \n");
        printf("2- Lecture d'un fichier \n");
        printf("0- Quitter \n");
        printf("> ");
        fgets(input, 256, stdin);

        if (strcmp(input, "1\n") == 0){
            interactive_mode();
        }
        else if (strcmp(input, "2\n") == 0) {
            read_file_mode();
        }
        else if (strcmp(input, "0\n") == 0) {
            printf("Sortie du programme.\n");
            return 0;
        }
        else {
            printf("Entrée invalide \n");
        }
    }

}


