#include <cs50.h>
#include <stdio.h>

int main(void)
{   
    int water;
    int bottles;
    printf("Minutes: ");
    do{
     water= get_int();
    }
    while (water<0);
    
    bottles = water*12;
    printf("Bottles: %i\n",bottles);
    
}