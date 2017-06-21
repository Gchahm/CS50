#include <cs50.h>
#include <stdio.h>

typedef struct sllist
{
    char* word;
    struct sllist* next;
}
sllnode;

sllnode* create(char* word);

sllnode* insert(sllnode* head, char* word));

bool find(sllnode* head, char* word));

void destroy(sllnode* head);

