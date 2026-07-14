#include <stdio.h>
#include <stdint.h>    // 組込みでは int でなく幅指定型を使う

#define LED_PIN (1u << 3)
#define UART_EN (1u << 0)
#define UART_BUSY (1u << 7)

int main(void) {
    uint32_t value = 0xFF;
    uint8_t reg=1;
    printf("初期値      : 0x%02X\n", reg);
    reg |= LED_PIN;
    printf("セット後    : 0x%02X\n", reg);
    reg &= ~LED_PIN;
    printf("クリア後    : 0x%02X\n", reg);
    reg ^= LED_PIN;
    printf("トグル後    : 0x%02X\n", reg);
    if(value & UART_BUSY){ 
        reg = (reg & ~0x0Fu) | (0x5u);
        printf("テスト     : 0x%02X\n", reg);
    }

    uint8_t high = (uint8_t)((value >> 8) & 0xFFu);

    printf("high=0x%02X \n", high);
    return 0;
}