#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{

if (argc == 2){
    string k = argv[1];
    bool shouldrun = true;
    int klen = strlen(k),j=0;
    for(int i=0;i<klen;i++){
    if(!isalpha(k[i])){
        shouldrun=false;
    }
    }
    if(shouldrun)
    {
    printf("plaintext: ");
    string p = get_string();
    
    
    for(int i=0,n=strlen(p);i<n;i++){
        int aindex = 0;
        k[j]=toupper(k[j]);
        if(j==klen){
            j=0;
        }
        if(isalpha(p[i])){
        if(islower(p[i])){
            aindex = ((int)p[i]-97+(int)k[j]-65)%26;
            p[i]=(char)aindex+97;
        }
        else{
            aindex = ((int)p[i]-65+(int)k[j]-65)%26;
            p[i]=(char)aindex+65;
        }
        
        j++;
    }
    }
        printf("ciphertext: %s\n",p);
}
else
{
    printf("error\n");
    return 1;
}
}
else
{
    printf("error\n");
    return 1;
}
}