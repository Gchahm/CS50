#include <cs50.h>
#include <stdio.h>
#include <string.h>
#define BASE (256)


unsigned long hash(const char *s, unsigned long m);

int main(void)
{   
    for(int i=0;i<10;i++)
    {
    printf("Type a string: ");
    string s = get_string();
    unsigned long teste = hash(s,15485863);
    printf("%long\n",teste);
    }

}


unsigned long hash(const char *s, unsigned long m)
{
    unsigned long h;
    unsigned const char *us;

    /* cast s to unsigned const char * */
    /* this ensures that elements of s will be treated as having values >= 0 */
    us = (unsigned const char *) s;

    h = 0;
    while(*us != '\0') {
        h = (h * BASE + *us) % m;
        us++;
    } 

    return h;
}