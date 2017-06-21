#include <cs50.h>
#include <stdio.h>

typedef struct dllist
{
    int number;
    struct dllist* prev;
    struct dllist* next;

}
dllnode;

dllnode* create(int value);
dllnode* insert(dllnode* head, int value);
bool find(dllnode* head, int value);
void destroy(dllnode* head);
void deletep(dllnode* target);


int main(void)
{
    dllnode* head = create(40);
    head = insert(head,20);
    head = insert(head,30);
    dllnode* todelete = head;
    head = insert(head,50);
    head = insert(head,10);
    if(find(head,30))
        printf("Found number\n");
    if(!find(head,11))
        printf("Didn't find number\n");
    deletep(todelete);
    destroy(head);
}

dllnode* create(int value){
    dllnode *dll = malloc(sizeof(dllnode));
    if(dll==NULL)
        return NULL;
    dll->number=value;
    dll->prev=NULL;
    dll->next = NULL;
    return dll;
}

bool find(dllnode* head,int value){
    dllnode* trav = head;
    while(trav!=NULL){
        if(trav->number==value)
            return true;
        trav=trav->next;
    }
    return false;
}

dllnode* insert(dllnode* head, int value){
    dllnode *dll = malloc(sizeof(dllnode));
    if(dll==NULL)
        return NULL;
    dll->number=value;
    dll->next = head;
    dll->prev=NULL;
    head->prev = dll;
    return dll;
}

void destroy(dllnode* head){
    dllnode *list = head;
    if(list!=NULL){
        dllnode* next = list->next;
        destroy(next);
        printf("deleted memory for number %i\n",list->number);
    }
    free(list);
}

void deletep(dllnode* target){
    dllnode* prev = target->prev;
    dllnode* next = target->next;
    if(target->prev!=NULL)
        prev->next=target->next;
    if(target->next!=NULL)
        next->prev=target->prev;
    printf("deleting node with number %i\n",target->number);
    free(target);
}