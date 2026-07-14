#include <stdint.h>
#include <stdio.h>

#define CLAMP(v, lo, hi) (((v)<(lo)) ? (lo) : (((v)>(hi)) ? (hi) : (v)))

uint8_t sat_add(uint8_t a, uint8_t b);

int main(){
    uint8_t sum = sat_add(100, 200);
    printf("100+200: %d\n", sum);
    sum = sat_add(0, 0);
    printf("0+0: %d\n", sum);
    sum = sat_add(255, 1);
    printf("255+1: %d\n", sum);

    int x = 2 * CLAMP(20, 0, 10);
    printf("x = %d\n", x);

    return 0;
}

uint8_t sat_add(uint8_t a, uint8_t b){
    uint16_t sum = (uint16_t)(a + b);

    if(sum>255) sum = 255;
    
    return (uint8_t)sum;
}