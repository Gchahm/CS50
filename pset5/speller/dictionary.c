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
    char _word[LENGTH];
/**
 * Returns true if word is in dictionary else false.
 */
 
//first it copies all the chars in lower case
//then it calls find in the index the hashfunction gives us.
bool check(const char *word)
{
    int len =strlen(word);
    for(int i=0;i<len;i++){
        if(isalpha(word[i]))
            _word[i]=tolower(word[i]);
        else    
            _word[i]=word[i];
    }
         
    _word[len]='\0';
    
    int index=getIndex(_word);
    if(find(hashMap[index],_word))
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
    if(dptr==NULL)
        return false;
    int index;
    while(fscanf(dptr,"%s",_word)!=EOF){
        dsize++;
        index = getIndex(_word);
        if (hashMap[index]==NULL){
            hashMap[index]=create(_word);
        }else{
        hashMap[index]=insert(hashMap[index],_word);
        }
        if(hashMap[index]==NULL){
            unload();
            return false;
        }
    }
    fclose(dptr);
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
