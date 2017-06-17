#include <cs50.h>
#include <stdio.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <time.h>
#include <unistd.h>
#include <crypt.h>
#include <string.h>
#include <ctype.h>

string getHashCode(string pass);

bool forceone(string hash);
bool forcetwo(string hash);
bool forcethree(string hash);
bool forcefour(string hash);


int main(int argc, string argv[])
{
if (argc == 2){
    
    if(forceone(argv[1])){
        
    }else if(forcetwo(argv[1])){
        
    }else if(forcethree(argv[1])){
        
    }else if(forcefour(argv[1])){
        
    }

    
}else{
    printf("Usage: ./crack hash\n");
    return 1;
}
}

bool forcefour(string hash){
    char pass[5];
    pass[4]='\0';
    string possibleValues ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    bool ok;
    for(int i=0;i<52;i++){
        pass[0]=possibleValues[i];
        for(int j=0;j<52;j++){
            pass[1]=possibleValues[j];
            for(int k=0;k<52;k++){
                pass[2]=possibleValues[k];
                for(int l=0;l<52;l++){
                    pass[3]=possibleValues[l];
                    string forceHash = getHashCode(pass);
                    ok = strcmp (forceHash, hash) == 0;
                    if(ok){
                    printf("%s\n",pass);
                    return ok;
                    }
                }
            }
        }
    }
    return false;
}

bool forcethree(string hash){
    char pass[4];
    pass[3]='\0';
    string possibleValues ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    bool ok;
    for(int j=0;j<52;j++){
        pass[0]=possibleValues[j];
        for(int k=0;k<52;k++){
            pass[1]=possibleValues[k];
            for(int l=0;l<52;l++){
                pass[2]=possibleValues[l];
                string forceHash = getHashCode(pass);
                ok = strcmp (forceHash, hash) == 0;
                if(ok){
                printf("%s\n",pass);
                return ok;
                }
            }
        }
    }
    return false;
}
bool forcetwo(string hash){
    char pass[3];
    pass[2]='\0';
    string possibleValues ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    bool ok;
    for(int k=0;k<52;k++){
        pass[0]=possibleValues[k];
        for(int l=0;l<52;l++){
            pass[1]=possibleValues[l];
            string forceHash = getHashCode(pass);
            ok = strcmp (forceHash, hash) == 0;
            if(ok){
            printf("%s\n",pass);
            return ok;
            }
        }
    }
    
    return false;
}
bool forceone(string hash){
    char pass[2];
    pass[1]='\0';
    string possibleValues ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    bool ok;
    for(int l=0;l<52;l++){
        pass[0]=possibleValues[l];
        string forceHash = getHashCode(pass);
        ok = strcmp (forceHash, hash) == 0;
        if(ok){
        printf("%s\n",pass);
        return ok;
        }
    }
    
    
    return false;
}


string getHashCode(string pass){
      unsigned long seed[2];
  char salt[] = "50........";
  const char *const seedchars =
    "./ABCDEFGHIJKLMNOPQRST"
    "UVWXYZabcdefghijklmnopqrstuvwxyz";
  char *password;
  int i;

  /* Generate a (not very) random seed.
     You should do it better than this... */
  seed[0] = time(NULL);
  seed[1] = getpid() ^ (seed[0] >> 14 & 0x30000);

  /* Turn it into printable characters from ‘seedchars’. */
  for (i = 0; i < 8; i++)
    salt[3+i] = seedchars[(seed[i/5] >> (i%5)*6) & 0x3f];

  /* Read in the user’s password and encrypt it. */
  password = crypt(pass, salt);

  return password;
}
