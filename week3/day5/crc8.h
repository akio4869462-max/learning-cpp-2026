#ifndef CRC8_H
#define CRC8_H

#include <cstdint>
#include <cstddef>

inline uint8_t crc8(const uint8_t* data, size_t len) {
    uint8_t crc = 0x00;               // 初期値

    for (size_t i = 0; i < len; i++) {
        crc ^= data[i];                // TODO①: まず現在のcrcに、そのバイトをXORする

        for (int bit = 0; bit < 8; bit++) {
            // TODO②: crcの最上位ビット(0x80)が立っているかを見る
            if(crc & 0x80){
                // 立っていれば: crcを1ビット左シフトしてから、多項式(0x07)とXOR
                crc <<= 1;
                crc ^= 0x07;
            }else{
                // 立っていなければ: 単に1ビット左シフトするだけ
                crc <<= 1;
            }
        }
    }

    return crc;
}

#endif