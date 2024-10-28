#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/error.h"

Token *inputs_error(Token *tokens) {
    int parentheses_balance = 0;
    int i = 0;


    if (tokens[0].type == TOKEN_IDENTIFIER && tokens[1].type == TOKEN_OPAREN) {
        printf("Erreur 1 : L'identifiant '%s' n'est pas une fonction valide.\n", tokens[0].value);
        exit(EXIT_FAILURE);
    }

    if (tokens[0].type == TOKEN_TYPE && tokens[1].type != TOKEN_IDENTIFIER) {
        printf("Erreur 1 : L'identifiant '%s' n'est pas une fonction valide.\n", tokens[0].value);
        exit(EXIT_FAILURE);
    }

    if (tokens[0].type == TOKEN_EOF) {
        printf("Erreur 2 : Input vide.\n", tokens[0].value);
        exit(EXIT_FAILURE);
    }

    if (tokens[0].type == TOKEN_IDENTIFIER && tokens[1].type == TOKEN_IDENTIFIER) {
        printf("Erreur 3 :'%s' n'est pas un type valide.\n", tokens[0].value);
        exit(EXIT_FAILURE);
    }

    if (tokens[0].type == TOKEN_IDENTIFIER && tokens[1].type == TOKEN_IDENTIFIER) {
        printf("Erreur 3 :'%s' n'est pas un type valide.\n", tokens[0].value);
        exit(EXIT_FAILURE);
    }

    while (tokens[i].type != TOKEN_EOF) {
        if (tokens[i].type == TOKEN_OPAREN) {
            parentheses_balance++;
        } else if (tokens[i].type == TOKEN_CPAREN) {
            parentheses_balance--;
            if (parentheses_balance < 0) {
                printf("Erreur 4 : Parenthese fermante sans parenthese ouvrante.\n");
                exit(EXIT_FAILURE);
            }
        }

        if (tokens[i].type == TOKEN_OPERATOR && tokens[i + 1].type == TOKEN_OPERATOR) {
            printf("Erreur 5 : Operateur '%s' suivi d'un autre operateur '%s'.\n", tokens[i].value, tokens[i + 1].value);
            exit(EXIT_FAILURE);
        }

        if (i != 0 && tokens[i].type == TOKEN_FONCTION) {
            printf("Erreur 6 : Fonction '%s' ne peut pas etre utiliser.\n", tokens[i].value);
            exit(EXIT_FAILURE);
        }

        if (tokens[i].type == TOKEN_ASSIGN) {
            if (strcmp(tokens[i - 1].value, "char") == 0) {
                if (tokens[i + 1].type != TOKEN_QUOT || tokens[i + 2].type != TOKEN_IDENTIFIER || tokens[i + 3].type != TOKEN_QUOT) {
                    printf("Erreur 7 : Opérateur '=' suivi de '%s' impossible. Attendu une valeur de type char entourée de guillemets.\n", tokens[i + 1].value);
                    exit(EXIT_FAILURE);
                }
            } else if (strcmp(tokens[i - 1].value, "int") == 0) {
                if (tokens[i + 1].type != TOKEN_IDENTIFIER && tokens[i + 1].type != TOKEN_NUMBER && tokens[i + 1].type != TOKEN_OPAREN) {
                    printf("Erreur 7 : Opérateur '=' suivi de '%s' impossible.\n", tokens[i + 1].value);
                    exit(EXIT_FAILURE);
                }
            }
        }


        if (tokens[i].type == TOKEN_TYPE && tokens[i + 1].type == TOKEN_IDENTIFIER && tokens[i + 2].type !=
            TOKEN_ASSIGN) {
            printf("Erreur 8 : Declaration de variable incorrecte. Attendu '=' apres '%s'.\n", tokens[i + 1].value);
            exit(EXIT_FAILURE);
        }

        if (tokens[i].type == TOKEN_OPERATOR && tokens[i + 1].type == TOKEN_EOF) {
            printf("Erreur 10 : Expression incomplete. Operateur '%s' sans operande.\n", tokens[i].value);
            exit(EXIT_FAILURE);
        }

        i++;
    }

    if (tokens[i - 1].type != TOKEN_SEMICOLON) {
        printf("Erreur 11 : Expression ne se termine pas par un ';'.\n");
        exit(EXIT_FAILURE);
    }

    if (parentheses_balance > 0) {
        printf("Erreur 12 : Parentheses non fermees.\n");
        exit(EXIT_FAILURE);
    }


    int has_assign_or_func_or_type = 0;

    for (int j = 0; tokens[j].type != TOKEN_EOF; j++) {
        if (tokens[j].type == TOKEN_ASSIGN || tokens[j].type == TOKEN_FONCTION || tokens[j].type == TOKEN_TYPE) {
            has_assign_or_func_or_type = 1;
            break;
        }
    }

    if (!has_assign_or_func_or_type) {
        printf("Erreur : Compilation impossible. Ni assignation, ni fonction, ni type trouvé.\n");
        exit(EXIT_FAILURE);
    }

    return tokens;
}