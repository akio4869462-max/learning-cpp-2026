/*
 * drill08_ringbuf.cpp — Week3: リングバッファ(テンプレート・固定容量)
 * make drill08 && ./drill08
 * 組込みの最重要部品。ISR→メインループのデータ受け渡しに使う。
 */
#include <cstdio>
#include <cstdint>
#include <array>
#include <cstddef>

static int failures = 0;
#define CHECK(name, cond) do { \
    if (cond) { std::printf("  PASS  %s\n", name); } \
    else      { std::printf("  FAIL  %s\n", name); failures++; } \
} while (0)

/* 固定容量リングバッファ。動的確保なし・例外なし。
 * head_: 次に書く位置 / tail_: 次に読む位置 / count_: 格納数
 * count_ を持つと「満杯」と「空」の区別が簡単になる(教材05章参照) */
template <typename T, std::size_t N>
class RingBuf {
public:
    /* 課題1: 満杯ならfalse。格納してhead_を進める(N で折り返す) */
    bool push(const T& v) {
        (void)v;              /* TODO */
        return false;
    }

    /* 課題2: 空ならfalse。取り出してtail_を進める */
    bool pop(T& out) {
        (void)out;            /* TODO */
        return false;
    }

    /* 課題3: 格納数 */
    std::size_t count() const {
        return 9999;          /* TODO */
    }

private:
    std::array<T, N> buf_{};
    std::size_t head_ = 0, tail_ = 0, count_ = 0;
};

int main(void) {
    RingBuf<uint8_t, 2> rb;
    uint8_t out = 0;

    puts("[基本動作]");
    CHECK("初期countは0",     rb.count() == 0);
    CHECK("push 1",           rb.push(1));
    CHECK("push 2",           rb.push(2));
    CHECK("満杯pushはfalse",  rb.push(3) == false);
    CHECK("count==2",         rb.count() == 2);
    CHECK("pop -> 1(FIFO)",   rb.pop(out) && out == 1);
    CHECK("pop -> 2",         rb.pop(out) && out == 2);
    CHECK("空popはfalse",     rb.pop(out) == false);

    puts("[折り返し(ここがリングバッファの本体)]");
    RingBuf<int, 3> rb3;
    rb3.push(10); rb3.push(20); rb3.push(30);
    int v = 0;
    rb3.pop(v);                       /* 10が抜けて1個空く */
    CHECK("折り返しpush",     rb3.push(40));   /* head_が先頭に折り返す */
    CHECK("順序維持 20",      rb3.pop(v) && v == 20);
    CHECK("順序維持 30",      rb3.pop(v) && v == 30);
    CHECK("順序維持 40",      rb3.pop(v) && v == 40);

    puts("[大量データで折り返しを何周も]");
    RingBuf<int, 7> rb7;
    bool ok = true;
    for (int i = 0; i < 1000; i++) {
        if (!rb7.push(i)) { ok = false; break; }
        int got = -1;
        if (!rb7.pop(got) || got != i) { ok = false; break; }
    }
    CHECK("1000回 push/pop で順序が壊れない", ok);

    if (failures == 0) { puts("\nALL PASS! 次: drill09(状態機械)へ"); return 0; }
    std::printf("\n%d 件 FAIL\n", failures);
    return 1;
}
