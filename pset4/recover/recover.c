#include <cs50.h>
#include <stdio.h>
#include <stdint.h>

// define a type byte to better store the block
typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    
    //prevents wrong usage of the program
    if(argc!=2){
        fprintf(stderr,"Usage: ./recover raw\n");
        return 1;
    }
    
    char *rawfile = argv[1];
    
    //try to open the file
    FILE *rawptr = fopen(rawfile, "r");
    if (rawptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", rawfile);
        return 2;
    }
    
    //create the variable that will hold the block
    BYTE buffer[512]; 
    //creates a variable to hold file name and a counter to get them organized
    char filename[8]="000.jpg\0";
    int filenumber=0;
    // flag to tell the program when it should start writing and if it should close previous file or not.
    bool first=true;
    FILE *img;
    //fread return 0 if it can't find a block of 512 bytes anymore so we'll keep the loop until that happens
    while(fread(buffer,512,1,rawptr)!=0){
    //checks if the currect block is the start of a file
        if(buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3]&0xf0)==0xe0)
        {
    //The first time it finds a jpeg it'll only open a new filestream and set the flag to false
    //The second time it should close the previous file and open a new one
        if(first){
        img = fopen(filename,"w");   
        first=false;
        }else{
        fclose(img);
        img = fopen(filename,"w");
        }
        //sets the next file name to be old+1
        filenumber++;
        sprintf(filename,"%03i.jpg",filenumber);
        }
        //check if there is a file open to start writing
        if(first==false){
            fwrite(buffer,512,1,img);
        }
    }
    //close the last image
    fclose(img);
        
return 0;
}