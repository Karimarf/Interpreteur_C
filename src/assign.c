#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lexer.h"
#include "../include/assign.h"

NodeList * list = NULL;

// FONCTION DE DEBUG
void print_all_variables()
{
    NodeList *ptr = list;
    while (ptr != NULL)
    {
        printf("Variable: %s, Valeur: %d\n", ptr->key, ptr->value);
        ptr = ptr->next;
    }
}


void ajout(char* key, int value)
{
    NodeList *link = malloc(sizeof(NodeList));
    link->key = malloc(strlen(key) + 1);
    strcpy(link->key, key);
    link->value = value;

    link->next = list;
    list = link;

}




int recher(char* key)
{
    NodeList *ptr = list;
    while (ptr != NULL)
    {
        if(strcmp(ptr->key, key) == 0)
        {
            return ptr->value;
        }
        ptr = ptr->next;
    }
    return 0;
}



void modif(char* key, int value)
{
    NodeList *ptr = list;
    while (ptr != NULL)
    {
        if(strcmp(ptr->key, key) == 0)
        {
            ptr->value = value;
            return;
        }
        ptr = ptr->next;
    }
}



int print_v(Token * token)
{
    return recher(token->value);
}

int check_if_defined(char* key)
{
    NodeList *ptr = list;
    while (ptr != NULL)
    {
        if(strcmp(ptr->key, key) == 0)
        {
            return 1;
        }
        ptr = ptr->next;
    }
    return 0;
}