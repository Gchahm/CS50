/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include "helpers.h"
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    for(int i=0;i<n;i++){
        if(value==values[i]){
            return true;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int countAr[65537]={[0 ... 65536] = 0};;
    
    for(int i=0;i<n;i++){
        countAr[values[i]]+=1;
    }
    int n1=0;
    for(int i=0;i<65537;i++){
        if(countAr[i]>0){
            for(int j=0;j<countAr[i];j++){
                values[n1]=i;
                n1++;
            }
        }
    }
    return;
}
