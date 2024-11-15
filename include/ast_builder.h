#ifndef AST_H
#define AST_H

#include <lexer.h>


typedef struct Node {
    Token * token;
    struct Node* leftNode;
    struct Node* rightNode;

}Node;

typedef struct StackItem {
    Node* nodeStack;
    struct StackItem* nextItem;

}StackItem;

typedef struct {
    StackItem* stackHead;
}Stack;

void initStack(Stack* stack);
int isEmpty(Stack* stack);
Node* createNode(Token* token);
StackItem* createStackItem(Node* node);
void push(Stack* stack, Node* node);
Node* pop(Stack* stack);
Node* create_ast(Token* shunting_yd_exp);
void printAst(Node* node);
void displayAST(Node* node, int level);
int evaluate(Node* node);
void freeAST(Node* node);


#endif