#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int getIndex(char* a);

int main(void)
{
    FILE* dptr = fopen("large","r");
    char word[46];
    int hashtable[600],count[600];
    for(int i=0;i<600;i++){
        hashtable[i]=0;
        count[i]=0;
    }
        
    //creates the hash table and sets the ammount of words each position will hold
    while(fscanf(dptr,"%s",word)!=EOF){
        hashtable[getIndex(word)]++;
    }
    int total=0,min,max,mean,median;
    //iterates over the hashtable to get statistics
    for(int i=0;i<600;i++){
        printf("Index %i words %i\n",i,hashtable[i]);
        total+=hashtable[i];
        count[hashtable[i]]++;
    }
    int countindex=0;
    for(int i=0;i<600;i++){
        for(int j=0,k=count[i];j<k;j++){
            hashtable[countindex]=i;
            countindex++;
        }
    }
    mean=total/600;
    min=hashtable[0];
    max=hashtable[599];
    median=(hashtable[299]+hashtable[300])/2;
    printf("total: %i min: %i max: %i mean: %i median: %i \n",total,min,max,mean,median);
    char* myname = "Gustavo";
    int myindex = getIndex(myname);
    printf("Index for %s is %i\n",myname,myindex);
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