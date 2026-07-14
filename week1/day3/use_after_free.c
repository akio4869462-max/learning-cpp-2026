#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(){
    int *p = malloc(10);
    
    free(p);

    printf("%d\n",p[0]);

    return 0;
}