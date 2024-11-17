#include "../include/ast_builder.h"
#include <stdlib.h>
#include <stdio.h>



void initStack(Stack* stack) {
    stack->stackHead = NULL;
}

int isEmpty(Stack* stack) {

    return stack->stackHead == NULL;
}

Node* createNode(Token* token) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->token = token;
    node->leftNode = NULL;
    node->rightNode = NULL;
    return node;
}

StackItem* createStackItem(Node* node) {
    StackItem* stackItem = (StackItem*)malloc(sizeof(StackItem));
    stackItem->nodeStack = node;
    stackItem->nextItem = NULL;
    return stackItem;
}

void push(Stack* stack, Node* node) {
    StackItem* newItem = createStackItem(node);
    if(!newItem) {
        printf("oof StackItem\n");
        return;
    }
    newItem->nextItem = stack->stackHead;
    stack->stackHead = newItem;

}

Node* pop(Stack* stack) {
    if(isEmpty(stack)) {
        return NULL;
    }
    else {
        Node* temp = stack->stackHead->nodeStack;
        StackItem* head =  stack->stackHead;
        stack->stackHead = head->nextItem;
        free(head);
        return temp;
    }


}


Node* create_ast(Token* shunting_yd_exp) {
    Stack stack;
    initStack(&stack);
    Node* Shunting_yard_nodes = NULL;
    for (int i = 0; shunting_yd_exp[i].type != TOKEN_EOF; i++) {
        Shunting_yard_nodes = createNode(&shunting_yd_exp[i]);
        if (!Shunting_yard_nodes) {
            printf("oof Node \n");
        }
        if(shunting_yd_exp[i].type == TOKEN_NUMBER) {
            push(&stack, Shunting_yard_nodes);
        } else if (shunting_yd_exp[i].type == TOKEN_OPERATOR) {
            Shunting_yard_nodes->rightNode = pop(&stack);
            Shunting_yard_nodes->leftNode = pop(&stack);
            push(&stack, Shunting_yard_nodes);
        }
    }
    return Shunting_yard_nodes;
}

void printAst(Node* node) {
    printf("%s \n", node->token->value);
    if(node->leftNode != NULL) {
        printf("Left: ");
        printAst(node->leftNode);
    }
    if(node->rightNode != NULL) {
        printf("Right: ");
        printAst(node->rightNode);
    }
}

void displayAST(Node* node, int level)
{
    if(node == NULL)
    {
        return;
    }

    if(level)
    {
        printf("%c[\"%s\"] \n", level + 'A', node->token->value);
    }
    int current = level;

    level++;

    if(node->leftNode)
    {
        printf("%c[\"%s\"] --> ", current + 'A', node->token->value);
        displayAST(node->leftNode, level);
    }

    level++;

    if(node->rightNode)
    {
        printf("%c[\"%s\"] --> ", current + 'A', node->token->value);
        displayAST(node->rightNode, level);
    }
}

int evaluate(Node* node) {
    if(node->leftNode == NULL && node->rightNode == NULL) {
        return atoi(node->token->value);
    }else {
        int tempLeft = evaluate(node->leftNode);
        int tempRight = evaluate(node->rightNode);
        switch(node->token->value[0]) {
            case '+':
                return tempLeft + tempRight;
            case '-':
                return tempLeft - tempRight;
            case '*':
                return tempLeft * tempRight;
            case '/':
                return tempLeft / tempRight;
            default:
                printf("Error\n");
                return 0;
        }
    }
}

void freeAST(Node* node) {
    if(node->leftNode == NULL && node->rightNode == NULL) {
        free(node);
    }else {
        evaluate(node->leftNode);
        evaluate(node->rightNode);
        free(node);
    }

}
