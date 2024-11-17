//
// Created by hvan on 16/10/2024.
//
#ifndef ASSIGN_H
#define ASSIGN_H

#include "lexer.h"
#include "ast_builder.h"

typedef struct NodeList
{
    char * key;
    int value;
    struct NodeList* next;
} NodeList;


extern void ajout(char * key, int value);
extern int recher(char * key);
extern void modif(char * key, int value);
int print_v(Token* token);
extern void print_all_variables();
extern int check_if_defined(char* key);


#endif