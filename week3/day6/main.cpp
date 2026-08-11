#include "OvenSystem.h"
#include <iostream>

// 動的確保なし・例外なしを保つため、ここでも FakeTempSensor(注入可能なテスト用実装)を使う。
// 実機では RealTempSensor(ADCレジスタを読む実装)を差し替えるだけでよい。
int main() {
    FakeTempSensor sensor;
    sensor.setValue(20.0);   // 起動時は目標(30度)より寒い状態からスタート

    OvenSystem sys(sensor);

    std::cout << "=== 環境制御シミュレータ 開始 ===" << std::endl;

    for (uint32_t ms = 0; ms <= 4000; ms += 10) {
        sys.tick(ms);

        if (ms == 1000) {
            // 1秒経過時点で「目標温度を26度に」というコマンドを外部から受信したことにする
            int16_t raw_value = 260;   // 26.0度 * 10
            uint8_t frame[] = {
                0xAA, 0x03, 0x01,
                static_cast<uint8_t>((raw_value >> 8) & 0xFF),
                static_cast<uint8_t>(raw_value & 0xFF),
                static_cast<uint8_t>(0xAA + 3 + 0x01 +
                    ((raw_value >> 8) & 0xFF) + (raw_value & 0xFF))
            };
            for (uint8_t b : frame) sys.receiveByte(b, ms);
        }

        if (ms == 2000) {
            sensor.setValue(200.0);   // センサー異常(範囲外)を模擬 → Errorへ
        }
        if (ms == 2100) {
            sensor.setValue(24.0);    // 正常値に戻す(1000ms後に自動復帰するはず)
        }
    }

    std::cout << "=== シミュレータ終了 ===" << std::endl;
}
