#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name = get_string();
    bool shouldprint = true;
    for(int i=0,n=strlen(name);i<n;i++){
        if(((int) name[i]) == 32){
            shouldprint = true;
        }
        else if(shouldprint){
            printf("%c",toupper(name[i]));
            shouldprint=false;
        }
    }
    printf("\n");
    
}