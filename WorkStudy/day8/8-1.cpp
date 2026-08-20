#include <cstdint>
#include <iostream>

int main(){
    uint32_t reg = 0;

    //(1)
    reg |= (1u << 3);
    reg |= (1u << 7);

    printf("%08X\n", reg);
    
    //(2)
    reg &= ~(1u << 3);
    printf("%08X\n", reg);
    
    //(3)
    if(reg & (1u << 7)) std::cout << "7bit is ON" << std::endl; 
    
    //(4)
    reg &= ~(0xFu << 8);
    reg |= (0xAu << 8);

    printf("%08X\n", reg);
}