#include <cs50.h>
#include <stdio.h>
#include <string.h>
typedef struct sllist
{
    char word[40];
    struct sllist* next;
}
sllnode;

sllnode* create(char* value);
sllnode* insert(sllnode* head, char* value);
bool find(sllnode* head, char* value);
void destroy(sllnode* head);

int main(void)
{   
    string teste = "test";
    sllnode* head = create(teste);
    teste = "gustavo";
    head = insert(head,teste);
    head = insert(head,"isabela");
    head = insert(head,"chloe");
    head = insert(head,"teste2");
    if(find(head,"gustavo"))
        printf("Found word\n");
    if(!find(head,"gdsustavo"))
        printf("Didn't find word\n");
    destroy(head);
}

sllnode* create(char* value){
    sllnode *ssl = malloc(sizeof(sllnode));
    if(ssl==NULL)
        return NULL;
    strcpy(ssl->word,value);
    ssl->next = NULL;
    return ssl;
}

sllnode* insert(sllnode* head, char* value){
    sllnode *ssl = malloc(sizeof(sllnode));
    if(ssl==NULL)
        return NULL;
    strcpy(ssl->word,value);
    ssl->next = head;
    return ssl;
}

bool find(sllnode* head,char* value){
    sllnode* trav = head;
    while(trav!=NULL){
        if(strcmp(trav->word,value)==0)
            return true;
        trav=trav->next;
    }
    return false;
}

void destroy(sllnode* head){
    sllnode *list = head;
    if(list!=NULL){
        sllnode* next = list->next;
        destroy(next);
        printf("deleted memory for word %s\n",list->word);
    }
    free(list);
}