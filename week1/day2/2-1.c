#include <stdlib.h>
#include <stdio.h>

int main(){
    int x = 42;
    int *p = &x;

    *p = 100;

    printf("adress: %p x: %d\n", (void *)p, x);
}