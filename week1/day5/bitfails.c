#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(){
    uint8_t a = 200, b = 100;
    uint8_t sum = a + b;

    printf("%d\n", sum);

    unsigned int u = 1;
    int i = -1;

    if(i < u){
        printf("i < u\n");
    }else{
        printf("i > u\n");
    }
    printf("u: %u, i: %u\n", u, i);

    size_t n = 3;
    size_t j = n - 1;
    int watchdog = 0;

    for (; j >= 0 ; j--) {
        printf("j = %zu\n", j);   // %zu は size_t 用の書式指定子
        watchdog++;
        if (watchdog > 5) break;   // 安全装置: 5回見たら強制的に抜ける
    }

    size_t k = 5;
    if (k >= 0) { printf("always true\n"); }

    return 0;
}