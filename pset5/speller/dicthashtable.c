/**
 * Implements a dictionary's functionality.
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

sllnode* hashMap[mapSize];
int dsize=0;
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    int len =strlen(word);
    char value[len+1];
    
    for(int i=0;i<len;i++){
        if(isalpha(word[i]))
            value[i]=tolower(word[i]);
        else    
            value[i]=word[i];
    }
         
    value[len]='\0';
    
    int index=getIndex(value);
    if(find(hashMap[index],value))
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
    int index;
    while(fscanf(dptr,"%s",word)!=EOF){
        dsize++;
        index = getIndex(word);
        if (hashMap[index]==NULL){
            hashMap[index]=create(word);
        }else{
        hashMap[index]=insert(hashMap[index],word);
        }
        if(hashMap[index]==NULL){
            unload();
            return false;
        }
    }
    free(dptr);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dsize;
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
/**
 * returns a index for each word from the dictionary
 * created by myself and tested in /dictionaries
 * it distributes evenly the words in lage into an array size 600
 */
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