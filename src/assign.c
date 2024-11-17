#include <../include/assign.h>
#include <stdio.h>
#include <stdlib.h>
#include <../include/lexer.h>
#include <../include/my_parser.h>
#include <../include/ast_builder.h>
#include <string.h>


Token * expression_assign(Token * tokens)
{
    int i=0;
    Token * assign_token = malloc(255 * sizeof(Token));
    int token_count = 0;

    while (tokens[i].type != TOKEN_EOF)
    {
        if(tokens[i].type == TOKEN_IDENTIFIER)
        {
            assign_token[token_count++] = tokens[i++];
            if(tokens[i].type == TOKEN_ASSIGN)
            {
                assign_token[token_count++] = tokens[i++];
                while(tokens[i].type != TOKEN_SEMICOLON && tokens[i].type != TOKEN_EOF)
                {
                    assign_token[token_count++] = tokens[i++];
                }
                if(tokens[i].type == TOKEN_SEMICOLON)
                {
                    assign_token[token_count++] = tokens[i++];
                }
                break;
            }
        }
        i++;
    }
    assign_token[token_count] = *create_token(TOKEN_EOF, "EOF");
    return assign_token;
}



NodeList * list = NULL;

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



void assign(Token * assign_token)
{
    char * var_name = assign_token[0].value;
    Token * value_token = malloc(255 * sizeof(Token));
    int value_token_count = 0;
    for (int i = 2; assign_token[i].type != TOKEN_EOF; i++)
    {
        value_token[value_token_count++] = assign_token[i];
    }
    value_token[value_token_count] = *create_token(TOKEN_EOF, "EOF");

    Node * value_node = create_ast(shunting_yard(value_token));
    int value = evaluate(value_node);
    displayAST(value_node, 0);
    if(recher(var_name))
    {
        modif(var_name, value);
    }else
    {
        ajout(var_name, value);
    }
    free(value_token);
}