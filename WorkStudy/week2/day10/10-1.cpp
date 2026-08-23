#include<cstdint>
#include<iostream>

void buidframe(uint8_t* f, uint8_t cmd, uint16_t data){
    f[0] = 0xA5;
    f[1] = cmd;
    f[2] = data & 0xff;
    f[3] = (data >> 8) & 0xff;
    f[4] = f[0] + f[1] + f[2] + f[3];
    f[5] = 0x5A;
}

bool parseFrame(const uint8_t* f, uint8_t* cmd, uint16_t* data){
    if(f[0] != 0xA5){
        std::cout << "header fail" << std::endl;
        return false;
    }
    if(f[5] != 0x5A){
        std::cout << "footer fail" << std::endl;
        return false;
    }
    if(f[4] != (f[0] + f[1] + f[2] + f[3])){
        std::cout << "check sum fail" << std::endl;
        return false;
    }
    *cmd = f[1];
    *data = f[2] | (f[3] << 8);
    return true;
}

int main() {
    uint8_t f[6];
    buidframe(f, 0x01, 0x1234);

    uint8_t cmd = 0;
    uint16_t data = 0;
    bool ok = parseFrame(f, &cmd, &data);
    std::printf("ok=%d cmd=%02X data=%04X\n", ok, cmd, data);

    f[2] ^= 0xFF; // わざと1バイト壊す
    ok = parseFrame(f, &cmd, &data);
    std::printf("ok=%d (corrupted)\n", ok);
    return 0;
}