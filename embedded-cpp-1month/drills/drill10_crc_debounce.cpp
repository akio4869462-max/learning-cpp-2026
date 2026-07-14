/*
 * drill10_crc_debounce.cpp — Week3 Day2-3: CRC-8とチャタリング除去
 * make drill10 && ./drill10
 */
#include <cstdio>
#include <cstdint>
#include <cstddef>

static int failures = 0;
#define CHECK(name, cond) do { \
    if (cond) { std::printf("  PASS  %s\n", name); } \
    else      { std::printf("  FAIL  %s\n", name); failures++; } \
} while (0)

/* 課題1: CRC-8(多項式0x07、初期値0x00)
 * アルゴリズム:
 *   各バイトについて: crc ^= byte
 *   その後8回: crcの最上位ビットが1なら (crc << 1) ^ 0x07、そうでなければ crc << 1
 *   (uint8_tに収まるようキャストを忘れずに)
 * FPGA経験者向け: これはLFSRそのもの */
uint8_t crc8(const uint8_t* data, std::size_t len) {
    (void)data; (void)len;    /* TODO */
    return 0xEE;              /* 仮実装 */
}

/* 課題2: チャタリング除去(シフトレジスタ方式)
 * 毎周期 raw を history_ の最下位に押し込み、
 *   下位4bitが全部1 -> stable_ = true
 *   下位4bitが全部0 -> stable_ = false
 * を判定して stable_ を返す */
class Debouncer {
public:
    bool update(bool raw) {
        (void)raw;            /* TODO */
        return stable_;
    }
private:
    uint8_t history_ = 0;
    bool stable_ = false;
};

int main(void) {
    puts("[crc8]");
    const uint8_t tv[] = {'1','2','3','4','5','6','7','8','9'};
    CHECK("標準テストベクタ \"123456789\" -> 0xF4", crc8(tv, 9) == 0xF4);
    CHECK("空データ -> 0x00", crc8(tv, 0) == 0x00);
    const uint8_t one[] = { 0x01 };
    CHECK("{0x01} -> 0x07(多項式そのもの)", crc8(one, 1) == 0x07);

    puts("[Debouncer]");
    Debouncer db;
    CHECK("1回目のtrueでは確定しない", db.update(true) == false);
    CHECK("2回目もまだ",               db.update(true) == false);
    CHECK("3回目もまだ",               db.update(true) == false);
    CHECK("4回連続でON確定",           db.update(true) == true);
    CHECK("1回falseでも保持(耐ノイズ)", db.update(false) == true);
    CHECK("2回目のfalseも保持",         db.update(false) == true);
    CHECK("3回目のfalseも保持",         db.update(false) == true);
    CHECK("4回連続falseでOFF確定",      db.update(false) == false);

    puts("[Debouncer: チャタリング波形]");
    Debouncer db2;
    /* 1,0,1,0 と暴れてから 1,1,1,1 で安定するボタン */
    const bool wave[] = { true, false, true, false, true, true, true, true };
    bool last = false;
    for (bool b : wave) last = db2.update(b);
    CHECK("暴れの間は確定せず最後に安定してON", last == true);

    if (failures == 0) { puts("\nALL PASS! Week3の部品が揃った。週次課題へ"); return 0; }
    std::printf("\n%d 件 FAIL\n", failures);
    return 1;
}
