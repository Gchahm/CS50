#include <cs50.h>
#include <stdio.h>


int main(void)
{
    long long cc_number;
    do{
    printf("Number: ");
    cc_number = get_long_long();
    }while(cc_number<0);
    
    int digit;
    bool multiple = false;
    int final_number = 0;
    int first_two = 0;
    int count=0;
    
    while(cc_number != 0)
    {
        digit =  cc_number %10;
        cc_number /= 10;
        
        if(multiple){
            digit *= 2;
            final_number += digit%10;
            final_number += digit/10;
        }
        else{
        final_number += digit;
        }
        multiple = (multiple) ? false : true ;
        if(cc_number<100 & cc_number>10){
            first_two = cc_number;
        }
        ++count;
        }
    if(final_number%10==0 & count>12 & count<17){
        if(first_two==37 || first_two==34){
            printf("AMEX\n");
        }
        else if(first_two>50 & first_two<56){
            printf("MASTERCARD\n");
        }
        else if(first_two>=40 & first_two<50){
            printf("VISA\n");
        }
    }
    else{
            printf("INVALID\n");    
    }
    
}