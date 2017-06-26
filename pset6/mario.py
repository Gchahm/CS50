#!/usr/bin/env python3

import cs50

def main():

    while(True):
        print("Type the pyramid's height:",end="")
        height = cs50.get_int()
        if height>0 and height<24:
                break

    for i in range(1,height+1):
        print(" "*(height-i),end="")
        print("#"*i,end="")
        print("  ",end="")
        print("#"*i,end="")
        print()

if __name__ == "__main__":
    main()