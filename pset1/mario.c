#include <cs50.h>
#include <stdio.h>

void block(int i );

int main(void)
{
int heigh;

do{
    printf("Heigh: ");
    heigh = get_int();
}
while(heigh<0 || heigh>23);
for(int i=1;i<=heigh;i++){
    for(int j=heigh;j>i;j--){
        printf(" ");
    }
    block(i);
    printf("  ");
    block(i);
    printf("\n");
}

}

void block(int i)
{
    for(int j=1;j<=i;j++){
        printf("#");
    }
}