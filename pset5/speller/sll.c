#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "sll.h"


//creates a new head node with next set to null.
sllnode* create(char* value){
    sllnode *sll = malloc(sizeof(sllnode));
    if(sll==NULL)
        return NULL;
    strcpy(sll->word,value);
    sll->next = NULL;
    return sll;
}

//creates a new node and points it's next to the old head node
sllnode* insert(sllnode* head, char* value){
    sllnode *sll = malloc(sizeof(sllnode));
    if(sll==NULL)
        return NULL;
    strcpy(sll->word,value);
    sll->next = head;
    return sll;
}
//goes over each node and tries to find the word if it finds it returns true
//if it finished all nodes and it returns false
bool find(sllnode* head,char* value){
    sllnode* trav = head;
    while(trav!=NULL){
        if(strcmp(trav->word,value)==0)
            return true;
        trav=trav->next;
    }
    return false;
}
//the fuction below is not in used but it'd be a way of counting how many blocks are there in a sll.
unsigned int nodeSize(sllnode* head,unsigned int* count){
    sllnode *list = head;
    if(list!=NULL){
        sllnode* next = list->next;
        nodeSize(next,count);
    }
    *count = *count+1;
    return *count;
}

void destroy(sllnode* head){
    sllnode *list = head;
    if(list!=NULL){
        sllnode* next = list->next;
        destroy(next);
    }
    free(list);
}