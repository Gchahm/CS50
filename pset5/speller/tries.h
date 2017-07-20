#include <cs50.h>
#include <stdio.h>


typedef struct node
{
    bool isword;
    struct node* children[27];
}
node;

node* create();

void destroy(node* root);

unsigned int nodeSize(node* root,unsigned int *count);