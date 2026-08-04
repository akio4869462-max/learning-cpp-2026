#include <cstdint>
#include <cstddef>
#include <iostream>

uint8_t crc8(const uint8_t* data, size_t len) {
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

int main() {
    // TODO③: テストベクタで検証
    // 例: {0x00} のCRC-8は何になるはずか、調べて確認する
    uint8_t test[] = {0x00};
    uint8_t result = crc8(test, 1);
    std::cout << static_cast<int>(result) << std::endl;
    uint8_t test2[] = {'1','2','3','4','5','6','7','8','9'};
    uint8_t result2 = crc8(test2, 9);
    std::cout << static_cast<int>(result2) << std::endl;   // 244 になるはず

}
