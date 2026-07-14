#include <stdio.h>
#include <stdint.h>    // 組込みでは int でなく幅指定型を使う

int main(void) {
    uint8_t  flags = 0x00;     // 8bit符号なし。HDLの reg [7:0] 相当の感覚
    uint16_t addr  = 0x1000;
    uint32_t value = 0;
    int32_t  temp  = -5;

    printf("flags=0x%02X addr=0x%04X value=%u temp=%d\n", flags, addr, value, temp);
    return 0;
}