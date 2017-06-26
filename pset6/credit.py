#!/usr/bin/env python3

import cs50

def main():
    while(True):
        print("Card number: ",end="")
        ccnumber = cs50.get_int()
        if ccnumber>0:
            break
       
    multiply = False
    fnumber = 0
    count=0
    while ccnumber!=0:
        digit = ccnumber%10
        ccnumber //= 10
    
        if multiply==True:
            digit*=2
            fnumber+=digit%10
            fnumber+=digit//10
            multiply=False
        else:
            fnumber+=digit
            multiply=True
        count+=1
        if ccnumber<100 and ccnumber>10:
            first_two = ccnumber

    if fnumber%10==0 and count>12 and count<17:
        if first_two==37 or first_two==34:
            print("AMEX")
        
        elif first_two>50 and first_two<56:
            print("MASTERCARD")
        
        elif first_two>=40 and first_two<50:
            print("VISA")
    else:
            print("INVALID")    
    
if __name__ == "__main__":
    main()