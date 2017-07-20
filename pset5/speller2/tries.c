#include <cs50.h>
#include <stdio.h>
#include "tries.h"

node* create(){
    node *ssl = malloc(sizeof(node));
    if(ssl==NULL)
        return NULL;
    for(int i=0;i<27;i++)
        ssl->children[i] = NULL;
    ssl->isword = false;
    return ssl;
}

void destroy(node* root){
    node* trav = root;
    for(int i=0;i<27;i++){
        if(trav->children[i]!=NULL){
            node* next=trav->children[i];
            destroy(next);
        }
    }
    free(trav);
}

unsigned int nodeSize(node* root,unsigned int* count){
        node* trav = root;
    for(int i=0;i<27;i++){
        if(trav->children[i]!=NULL){
            node* next=trav->children[i];
            nodeSize(next,count);
        }
    }
    if(trav->isword)
        *count = *count+1;
    return *count;
}