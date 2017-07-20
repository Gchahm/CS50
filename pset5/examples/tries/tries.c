#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
//this is a simple desmonstration of a hashtable

typedef struct node
{
    bool isword;
    struct node* children[27];
}
node;

void insert(node* root,char* word);
bool find(node* root,char* word);
int getIndex(char i);
node* create();
void destroy(node* root);

int main(void)
{
    
    node* root=create();
    if(root==NULL)
        return 1;
    char* word = "test";
    insert(root,word);
    if(find(root,"este"))
        printf("found este\n");
    if(find(root,"TEST")){
        printf("found test\n"); 
    }
    destroy(root);
}

void insert(node* root,char* word){
    node* trav = root;
    for(int i=0;i<strlen(word);i++){
        char* letter = &word[i];
        int  index = getIndex(*letter);
        if(trav->children[index]==NULL)
            trav->children[index]=create();
        trav=trav->children[index];
    }
    trav->isword=true;
}

bool find(node* root,char* word){
    node* trav = root;
    for(int i=0;i<strlen(word);i++){
        char* letter = &word[i];
        int  index = getIndex(*letter);
        if(trav->children[index]==NULL)
            return false;
        trav=trav->children[index];
    }
    if(trav->isword==true)
        return true;
    return false;
}

int getIndex(char i){
    if(isalpha(i))
        return (int)tolower(i)-97;
    return 27;
}

//the functions below are the only 2 needed to manipulate the structure(in my case)

node* create(){
    node *ssl = malloc(sizeof(node));
    if(ssl==NULL)
        return NULL;
    for(int i=0;i<27;i++)
        ssl->children[i] = NULL;
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




