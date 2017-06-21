#include <cs50.h>
#include <stdio.h>

typedef struct node
{
    bool is_word;
    struct node *children[27]
}
node;

int main(void)
{
    
}

void add(struct node,char * a){
        int position = getPosition(a);
        (if node->children )
}

void getPosition(char * a){
    if(a=='\'')
        return 26;
    if(isupper(a))
        return ((int) a) -65;
    if(islower(a))
        return((int)a-97);
}