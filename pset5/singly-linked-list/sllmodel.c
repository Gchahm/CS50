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

sllnode* create(int value){
    sllnode *ssl = malloc(sizeof(sllnode));
    if(ssl==NULL)
        return NULL;
    ssl->number=value;
    ssl->next = NULL;
    return ssl;
}

bool find(sllnode* head,int value){
    sllnode* trav = head;
    while(trav!=NULL){
        if(trav->number==value)
            return true;
        trav=trav->next;
    }
    return false;
}

sllnode* insert(sllnode* head, int value){
    sllnode *ssl = malloc(sizeof(sllnode));
    if(ssl==NULL)
        return NULL;
    ssl->number=value;
    ssl->next = head;
    return ssl;
}

void destroy(sllnode* head){
    sllnode *list = head;
    if(list!=NULL){
        sllnode* next = list->next;
        destroy(next);
    }
    free(list);
}