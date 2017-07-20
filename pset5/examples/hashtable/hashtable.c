#include <cs50.h>
#include <stdio.h>
//this is a simple desmonstration of a hashtable

#include "sll.h"

int hashfunc(int i);

int main(void)
{
 int hashsize = 2;
 sllnode* hashtable[hashsize];
 for(int i=0;i<hashsize;i++)
    hashtable[i]=NULL;
 int number;
 do{
     printf("insert a number (zero to leave): ");
     number = get_int();
     int hashn = hashfunc(number);
     if(hashtable[hashn]==NULL)
      hashtable[hashn]=create(number);
     else
        hashtable[hashn]=insert(hashtable[hashn],number);
 }while(number!=0);
    destroy(hashtable[0]);
    destroy(hashtable[1]);
}


int hashfunc(int i){
    if(i%2==0)
        return 0;
    else
        return 1;
}
