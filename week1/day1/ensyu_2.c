#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define LED_PIN (1u << 2)
#define UART_BUSY (1u << 2)

uint8_t set_bit(uint8_t v, uint8_t mask);
uint8_t clear_bit(uint8_t v, uint8_t mask);
uint8_t toggle_bit(uint8_t v, uint8_t mask);
bool test_bit(uint8_t v, uint8_t mask);
uint8_t extract_field(uint8_t v, int msb, int lsb);

int main(){
    uint8_t value = 0xA5;
    value = set_bit(value, LED_PIN);
    printf("0x%X\n", value);
    value = clear_bit(value, LED_PIN);
    printf("0x%X\n", value);
    value = toggle_bit(value, LED_PIN);
    printf("0x%X\n", value);
    int check = test_bit(value, UART_BUSY);
    printf("%d\n", check);
    
    value = extract_field(value,5,2);
    printf("0x%X\n", value);

    return 0;
}

uint8_t set_bit(uint8_t v, uint8_t mask){
    v |= mask;
    return v;
}
uint8_t clear_bit(uint8_t v, uint8_t mask){
    v &= ~mask;
    return v;
}

uint8_t toggle_bit(uint8_t v, uint8_t mask){
    v ^= mask;
    return v;
}

bool test_bit(uint8_t v, uint8_t mask){
    return (v & mask) != 0;
}

uint8_t extract_field(uint8_t v, int msb, int lsb){
    int width = msb - lsb + 1;
    uint8_t mask = (1u << width) - 1u;

    return ((v >> lsb) & mask);
}