#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(){
    int *p = malloc(10);
    
    free(p);
    free(p);

    return 0;
}