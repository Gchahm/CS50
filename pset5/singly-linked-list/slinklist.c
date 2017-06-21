#include <cs50.h>
#include <stdio.h>
#include "ssl.h"

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



int main(void)
{
    sllnode* head = create(40);
    head = insert(head,20);
    head = insert(head,30);
    head = insert(head,50);
    head = insert(head,10);
    if(find(head,30))
        printf("Found number\n");
    if(!find(head,11))
        printf("Didn't find number\n");
    destroy(head);
}

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
        printf("deleted memory for number %i\n",list->number);
    }
    free(list);
}