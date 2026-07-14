/*
 * drill01_bits.c — Week1 Day1: ビット操作
 *
 * 使い方:
 *   1. 「TODO」の関数本体を実装する(仮実装のままでもコンパイルは通る)
 *   2. make drill01 && ./drill01
 *   3. すべて PASS になったら教材 Day1 の演習へ
 *
 * ルール: main() のテストコードは変更しない。
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

static int failures = 0;
#define CHECK(name, cond) do { \
    if (cond) { printf("  PASS  %s\n", name); } \
    else      { printf("  FAIL  %s\n", name); failures++; } \
} while (0)

/* 課題1: pos ビット目(0起点)を 1 にして返す */
uint32_t set_bit(uint32_t v, unsigned pos) {
    (void)pos;                /* TODO: 実装したらこの行を消す */
    return v;                 /* 仮実装 */
}

/* 課題2: pos ビット目を 0 にして返す */
uint32_t clear_bit(uint32_t v, unsigned pos) {
    (void)pos;                /* TODO */
    return v;
}

/* 課題3: pos ビット目を反転して返す */
uint32_t toggle_bit(uint32_t v, unsigned pos) {
    (void)pos;                /* TODO */
    return v;
}

/* 課題4: pos ビット目が 1 なら true */
bool test_bit(uint32_t v, unsigned pos) {
    (void)v; (void)pos;       /* TODO */
    return false;
}

/* 課題5: v[msb:lsb] を取り出して返す(HDLの部分選択相当)
 * ヒント: 幅 = msb - lsb + 1。幅32のとき 1u << 32 は未定義動作なので分岐が要る */
uint32_t extract_field(uint32_t v, unsigned msb, unsigned lsb) {
    (void)msb; (void)lsb;     /* TODO */
    return v;
}

/* 課題6: 立っているビットの数を返す
 * ヒント: v &= v - 1 は最下位の1を消す(Kernighan法) */
unsigned popcount32(uint32_t v) {
    (void)v;                  /* TODO */
    return 0;
}

int main(void) {
    puts("[set_bit]");
    CHECK("bit3を立てる",        set_bit(0x00u, 3) == 0x08u);
    CHECK("既に立っていても同じ", set_bit(0x08u, 3) == 0x08u);
    CHECK("他ビットは不変",      set_bit(0xF0u, 0) == 0xF1u);

    puts("[clear_bit]");
    CHECK("bit0を落とす",        clear_bit(0xFFu, 0) == 0xFEu);
    CHECK("既に0でも同じ",       clear_bit(0xFEu, 0) == 0xFEu);

    puts("[toggle_bit]");
    CHECK("0->1",                toggle_bit(0x00u, 4) == 0x10u);
    CHECK("2回で元に戻る",       toggle_bit(toggle_bit(0xA5u, 2), 2) == 0xA5u);

    puts("[test_bit]");
    CHECK("bit7=1を検出",        test_bit(0x80u, 7) == true);
    CHECK("bit0=0を検出",        test_bit(0x80u, 0) == false);

    puts("[extract_field]");
    CHECK("[15:8]の抽出",        extract_field(0xABCD1234u, 15, 8) == 0x12u);
    CHECK("[3:0]の抽出",         extract_field(0xABCD1234u, 3, 0) == 0x4u);
    CHECK("[31:0]=全体(境界!)",  extract_field(0xDEADBEEFu, 31, 0) == 0xDEADBEEFu);

    puts("[popcount32]");
    CHECK("0xF0F0F0F0は16個",    popcount32(0xF0F0F0F0u) == 16u);
    CHECK("0は0個",              popcount32(0u) == 0u);
    CHECK("1バイト全部",         popcount32(0xFFu) == 8u);

    if (failures == 0) { puts("\nALL PASS! 次: 教材 Week1 Day1 の演習へ"); return 0; }
    printf("\n%d 件 FAIL(未実装 or バグ)\n", failures);
    return 1;
}
