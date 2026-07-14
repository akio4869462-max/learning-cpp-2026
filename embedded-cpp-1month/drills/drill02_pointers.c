/*
 * drill02_pointers.c — Week1 Day2: ポインタ・配列・文字列
 * make drill02 && ./drill02
 */
#include <stdio.h>
#include <stddef.h>
#include <string.h>

static int failures = 0;
#define CHECK(name, cond) do { \
    if (cond) { printf("  PASS  %s\n", name); } \
    else      { printf("  FAIL  %s\n", name); failures++; } \
} while (0)

/* 課題1: 2つのintをポインタ経由で入れ替える */
void swap_int(int *a, int *b) {
    (void)a; (void)b;         /* TODO */
}

/* 課題2: 終端'\0'までの長さ(strlen自作。ライブラリ関数は使わない) */
size_t my_strlen(const char *s) {
    (void)s;                  /* TODO */
    return 0;
}

/* 課題3: strcmp自作。a<b なら負、等しければ0、a>b なら正
 * ヒント: charの符号は環境依存 → unsigned char で比較する */
int my_strcmp(const char *a, const char *b) {
    (void)a; (void)b;         /* TODO */
    return -12345;            /* 仮実装(わざと変な値) */
}

/* 課題4: 配列をin-placeで逆順にする(ポインタ2本: 先頭と末尾)
 * 注意: n==0 のとき arr + n - 1 を計算してはいけない */
void reverse(int *arr, size_t n) {
    (void)arr; (void)n;       /* TODO */
}

/* 課題5: targetのインデックスを返す。無ければ -1 */
int find(const int *arr, size_t n, int target) {
    (void)arr; (void)n; (void)target;   /* TODO */
    return -1;
}

int main(void) {
    puts("[swap_int]");
    int x = 1, y = 2;
    swap_int(&x, &y);
    CHECK("入れ替わる", x == 2 && y == 1);

    puts("[my_strlen]");
    CHECK("通常",       my_strlen("abc") == 3);
    CHECK("空文字列",   my_strlen("") == 0);

    puts("[my_strcmp]");
    CHECK("等しい",     my_strcmp("abc", "abc") == 0);
    CHECK("a < b",      my_strcmp("abc", "abd") < 0);
    CHECK("a > b",      my_strcmp("b", "abc") > 0);
    CHECK("前方一致",   my_strcmp("ab", "abc") < 0);

    puts("[reverse]");
    int a5[5] = {1, 2, 3, 4, 5};
    reverse(a5, 5);
    CHECK("奇数個", a5[0] == 5 && a5[2] == 3 && a5[4] == 1);
    int a2[2] = {7, 9};
    reverse(a2, 2);
    CHECK("2個",   a2[0] == 9 && a2[1] == 7);
    reverse(a2, 0);              /* クラッシュしないこと自体がテスト */
    CHECK("n=0でも安全", 1);

    puts("[find]");
    const int data[] = {10, 20, 30, 20};
    CHECK("先頭",       find(data, 4, 10) == 0);
    CHECK("重複は最初", find(data, 4, 20) == 1);
    CHECK("無い",       find(data, 4, 99) == -1);

    if (failures == 0) { puts("\nALL PASS! 次: drill03 へ"); return 0; }
    printf("\n%d 件 FAIL\n", failures);
    return 1;
}
