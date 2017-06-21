#include <cs50.h>
#include <stdio.h>

typedef struct sllist
{
    int number;
    struct sllist* next;
}
sllnode;

sllnode* create(int value);

sllnode* insert(sllnode* head, int value);

bool find(sllnode* head, int value);

void destroy(sllnode* head);

