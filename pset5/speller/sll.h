#include <cs50.h>
#include <stdio.h>

#include <string.h>
#include <ctype.h>

// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

typedef struct sllist
{
    char word[LENGTH];
    struct sllist* next;
}
sllnode;

sllnode* create(char* word);

sllnode* insert(sllnode* head, char* word);

bool find(sllnode* head,char* word);

void destroy(sllnode* head);

unsigned int nodeSize(sllnode* head,unsigned int* count);

int getIndex(char* a);