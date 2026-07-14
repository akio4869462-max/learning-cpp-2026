#include <stdio.h>
#include <stdint.h>

int main(){
    uint32_t value =0x12345678;
    uint8_t *p = (uint8_t *)&value;
    
    for(int i=0;i<4;i++){
        printf("%x ",p[i]);
    }
    printf("\n");

    return 0;
}