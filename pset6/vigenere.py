#!/usr/bin/env python3

import cs50
import sys

def main():
    if len(sys.argv)!=2:
        print("Usage: vigenere.py key")
        return 1
    if sys.argv[1].isalpha()==False:
        print("Only characters allowrd for the key")
        return 2
    print("Type the message to encode: ",end="")    
    message = cs50.get_string()
    j=0
    key = sys.argv[1].upper()
    keylen = len(sys.argv[1])
    for l in message:
        if l.isalpha():
            if l.islower():
                index = (ord(l)-97+ord(key[j])-65)%26
                l=chr(index+97)
                print(l,end="")
            if l.isupper():
                index = (ord(l)-65+ord(key[j])-65)%26
                l=chr(index+65)
                print(l,end="")
        else:
            print(l,end="")
        j=(j+1)%keylen
        
    print()
    return 0
    
if __name__ == "__main__":
    main()