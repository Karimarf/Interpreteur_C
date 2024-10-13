#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\include\error.h"

Token *inputs_error(Token *tokens) {
    int parentheses_balance = 0;
    int i = 0;

    // Vérification des erreurs pour les deux premiers tokens
    if (tokens[0].type == TOKEN_IDENTIFIER && tokens[1].type == TOKEN_OPAREN) {
        printf("Erreur : L'identifiant '%s' n'est pas une fonction valide.\n", tokens[0].value);
        exit(EXIT_FAILURE);
    }

    if (tokens[0].type == TOKEN_EOF) {
        printf("Erreur : Input vide.\n", tokens[0].value);
        exit(EXIT_FAILURE);
    }

    if (tokens[0].type == TOKEN_IDENTIFIER && tokens[1].type == TOKEN_IDENTIFIER) {
        printf("Erreur :'%s' n'est pas un type valide.\n", tokens[0].value);
        exit(EXIT_FAILURE);
    }

    while (tokens[i].type != TOKEN_EOF) {
        // Vérifier l'équilibrage des parenthèses
        if (tokens[i].type == TOKEN_OPAREN) {
            parentheses_balance++;
        } else if (tokens[i].type == TOKEN_CPAREN) {
            parentheses_balance--;
            if (parentheses_balance < 0) {
                printf("Erreur : Parenthèse fermante sans parenthèse ouvrante.\n");
                exit(EXIT_FAILURE);
            }
        }

        // Vérifier si un opérateur est suivi par un autre opérateur
        if (tokens[i].type == TOKEN_OPERATOR && tokens[i + 1].type == TOKEN_OPERATOR) {
            printf("Erreur : Operateur '%s' suivi d'un autre operateur '%s'.\n", tokens[i].value, tokens[i + 1].value);
            exit(EXIT_FAILURE);
        }

        if (i != 0 && tokens[i].type == TOKEN_FONCTION) {
            printf("Erreur : Fonction '%s' ne peut pas etre utiliser.\n", tokens[i].value);
            exit(EXIT_FAILURE);
        }

        // Vérifier si un '=' est suivie d'un identifier ou d'un nombre
        if (tokens[i].type == TOKEN_ASSIGN && tokens[i + 1].type != TOKEN_IDENTIFIER || tokens[i + 1].type ==
            TOKEN_NUMBER) {
            printf("Erreur : Operateur '%s' suivi de '%s' impoosible.\n", tokens[i].value, tokens[i + 1].value);
            exit(EXIT_FAILURE);
        }

        // Vérifier les déclarations de variable incorrectes (par exemple : int x ; au lieu de int x = ...)
        if (tokens[i].type == TOKEN_TYPE && tokens[i + 1].type == TOKEN_IDENTIFIER && tokens[i + 2].type !=
            TOKEN_ASSIGN) {
            printf("Erreur : Déclaration de variable incorrecte. Attendu '=' après '%s'.\n", tokens[i + 1].value);
            exit(EXIT_FAILURE);
        }

        if (tokens[i].type == TOKEN_OPERATOR && tokens[i + 1].type != TOKEN_OPAREN || tokens[i + 1].type != TOKEN_CPAREN) {
            printf("Erreur : Operateur '%s' suivie de '%s' incorrect'.\n", tokens[i].value , tokens[i+1].value );
            exit(EXIT_FAILURE);
        }

        // Vérifier si un opérateur est à la fin d'une expression (manque un opérande)
        if (tokens[i].type == TOKEN_OPERATOR && tokens[i + 1].type == TOKEN_EOF) {
            printf("Erreur : Expression incomplète. Opérateur '%s' sans opérande.\n", tokens[i].value);
            exit(EXIT_FAILURE);
        }

        i++;
    }

    // Vérifier que la dernière expression se termine par un ';'
    if (tokens[i - 1].type != TOKEN_SEMICOLON) {
        printf("Erreur : Expression ne se termine pas par un ';'.\n");
        exit(EXIT_FAILURE);
    }

    // Vérifier s'il manque des parenthèses fermantes
    if (parentheses_balance > 0) {
        printf("Erreur : Parenthèses non fermées.\n");
        exit(EXIT_FAILURE);
    }

    return tokens;
}