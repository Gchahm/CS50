#include <cs50.h>
#include <stdio.h>
#include "dictionary.h"



sllnode* create(char* word)){
    sllnode *ssl = malloc(sizeof(sllnode));
    if(ssl==NULL)
        return NULL;
    ssl->word=word;
    ssl->next = NULL;
    return ssl;
}


bool find(sllnode* head,char* word)){
    sllnode* trav = head;
    while(trav!=NULL){
        if(trav->word==word)
            return true;
        trav=trav->next;
    }
    return false;
}

sllnode* insert(sllnode* head, char* word)){
    sllnode *ssl = malloc(sizeof(sllnode));
    if(ssl==NULL)
        return NULL;
    ssl->word=word;
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