#include <stdio.h>
#include <stdint.h>

void print_bits(uint32_t v);

int main(){
    uint32_t value = 0xA5;
    print_bits(value);
    return 0;
}

void print_bits(uint32_t v){
    for(int i=31;i>=0;i--){
        printf("%d", (v >> i) & 1);
    }
    printf("\n");
}