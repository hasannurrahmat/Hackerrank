#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
/*
    menghitung banyaknya jumlah digits 0-9
*/
int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int* nums = (int*) malloc(10 * sizeof(int));
    int i;
    char c;
    
    for(i = 0; i < 10; i++)
        *(nums+i) = 0;

    while(scanf("%c", &c) == 1)
        if(c >= '0' && c <= '9')
            (*(nums+(c-'0')))++;
    
    for(i = 0; i < 10; i++)
        printf("%d ", *(nums+i));

    return 0;
}
