/**
 * Implements a dictionary's functionality.
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"
#include "sll.h"

int mapSize=600;
sllnode hashMap[mapSize];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    int index=getIndex(word);
    if(find(hashMap[index],word))
        return true;
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{   
    for(int i=0;i<mapSize;i++){
        hashMap[i]=NULL;
    }
    FILE* dptr = fopen(dictionary,"r");
    char word[LENGTH];
    while(fscanf(dptr,"%s",word)!=EOF){
        int index = getIndex(word);
        if (hashMap[index]==NULL)
            hashMap[index]=create(word);
        else
            hashMap[index]=insert(hashMap[index],word);
        if(hashMap[index]==NULL){
            unload();
            return false;
        }
    }
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for(int i=0;i<mapSize;i++){
        destroy(hashMap[i]);
    }
    return true;
}

int getIndex(char* a){
    int index=0, len=strlen(a);
    for(int i=0;i<len;i++){
        if(isalpha(a[i])){
            char b = tolower(a[i]);
            index+=((int)b);
        }
        else
            index+=100;
    }
    return index%600;
}