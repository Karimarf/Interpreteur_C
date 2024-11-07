//
// Created by hvan on 16/10/2024.
//
#ifndef ASSIGN_H
#define ASSIGN_H
#include "../include/lexer.h"
#include "../include/ast_builder.h"

typedef struct Assign
{
    Token* token;
    Node* leftNode;
    Node* rightNode;
} Assign;

typedef struct NodeList
{
    char * key;
    int value;
    struct NodeList* next;
} NodeList;


extern Token * expression_assign(Token* token);
extern void ajout(char * key, int value);
extern int recher(char * key);
extern void modif(char * key, int value);
int print_v(Token* token);
extern void print_all_variables();
extern void assign(Token* token);


#endif