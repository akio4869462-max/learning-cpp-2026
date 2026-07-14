/*
 * drill03_memory.c — Week1 Day3: 動的メモリ(malloc/realloc/free)
 * make drill03 && ./drill03
 * ALL PASS 後: make clean && make drill03 ASAN=1 && ./drill03 でリーク検査もすること!
 *   (destroyの実装が不完全だと LeakSanitizer が報告してくれる)
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int failures = 0;
#define CHECK(name, cond) do { \
    if (cond) { printf("  PASS  %s\n", name); } \
    else      { printf("  FAIL  %s\n", name); failures++; } \
} while (0)

typedef struct {
    int    *data;
    size_t  size;
    size_t  cap;
} IntStack;

/* 見本(実装済み): 確保失敗チェックの型を見ておくこと */
IntStack *stack_create(void) {
    IntStack *s = malloc(sizeof(IntStack));
    if (s == NULL) return NULL;
    s->cap = 2;                       /* わざと小さく: pushで必ず成長が起きる */
    s->size = 0;
    s->data = malloc(s->cap * sizeof(int));
    if (s->data == NULL) { free(s); return NULL; }
    return s;
}

/* 課題1: push。満杯なら realloc で容量を2倍に。成功true/失敗false
 * ヒント: realloc失敗時は元のポインタを壊さないこと(一時変数に受ける) */
bool stack_push(IntStack *s, int v) {
    (void)s; (void)v;         /* TODO */
    return false;
}

/* 課題2: pop。空ならfalse。値は *out へ */
bool stack_pop(IntStack *s, int *out) {
    (void)s; (void)out;       /* TODO */
    return false;
}

/* 課題3: 完全に解放する(dataとs本体の両方!)
 * 片方を忘れると ASAN=1 ビルドでリーク報告が出る */
void stack_destroy(IntStack *s) {
    (void)s;                  /* TODO */
}

int main(void) {
    IntStack *s = stack_create();
    CHECK("create", s != NULL);
    if (s == NULL) return 1;

    puts("[push/pop]");
    CHECK("push 1",  stack_push(s, 10));
    CHECK("push 2",  stack_push(s, 20));
    CHECK("push 3(ここでrealloc成長)", stack_push(s, 30));
    CHECK("size==3", s->size == 3);
    CHECK("capが成長している", s->cap >= 3);

    int v = 0;
    CHECK("pop -> 30(LIFO)", stack_pop(s, &v) && v == 30);
    CHECK("pop -> 20",       stack_pop(s, &v) && v == 20);
    CHECK("pop -> 10",       stack_pop(s, &v) && v == 10);
    CHECK("空のpopはfalse",  stack_pop(s, &v) == false);

    puts("[大量push(成長の連鎖)]");
    bool ok = true;
    for (int i = 0; i < 1000; i++) ok = ok && stack_push(s, i);
    CHECK("1000回push", ok && s->size == 1000);
    CHECK("先頭から正しく積まれている", s->data[0] == 0 && s->data[999] == 999);

    stack_destroy(s);
    CHECK("destroyがクラッシュしない", 1);

    if (failures == 0) {
        puts("\nALL PASS! 仕上げ: make clean && make drill03 ASAN=1 でリークゼロを確認");
        return 0;
    }
    printf("\n%d 件 FAIL\n", failures);
    return 1;
}
