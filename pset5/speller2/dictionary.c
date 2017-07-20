/**
 * Implements a dictionary's functionality.
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 */
  node* root;
 
bool check(const char *word)
{   
    node* trav = root;
    int index;
    for(int i=0;i<strlen(word);i++){
        if(isalpha(word[i]))
            index=(int)tolower(word[i])-97;
        else
            index=27; 
        if(trav->children[index]==NULL)
            return false;
        trav=trav->children[index];
    }
    if(trav->isword==true)
        return true;
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary){
   
    root=create();
    node* trav;
    FILE* dptr = fopen(dictionary,"r");
    if (dptr == NULL)
        return false;
    char word[LENGTH];
    int  index;
    while(fscanf(dptr,"%s",word)!=EOF){
        trav = root;
        for(int i=0;i<strlen(word);i++){
            if(isalpha(word[i]))
                index=(int)tolower(word[i])-97;
            else
                index=26; 
            if(trav->children[index]==NULL){
                trav->children[index]=create();
            if(trav->children[index]==NULL){
                unload();
                fclose(dptr);
                return false;
            }
            }
            trav=trav->children[index];
        }
        trav->isword=true;
        }
    fclose(dptr);
    return true;
}



/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    unsigned int value=0;
    nodeSize(root,&value);  
    return value;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    destroy(root);
    return true;
}
/**
 * returns a index for the current letter being looked at.
 */
int getIndex(char* a){
    if(isalpha(*a))
        return (int)tolower(*a)-97;
    return 27;
}