#include <stdlib.h>
#include <stdio.h>

int main(){
    int a[5] = {10, 20, 30, 40, 50};
    int *p = a;

    printf("p[2]: %d, *(a+2): %d\n", p[2], *(a+2));
    
    p++;

    printf("p++: %d\n", *p);

    // printf("%d\n", p[3]);
    // printf("%d\n", *(p + 3));

    size_t n = sizeof(a) / sizeof(a[0]);

    printf("%d\n", (int)n);

    return 0;
}