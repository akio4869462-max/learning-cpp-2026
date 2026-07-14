/*
 * drill04_struct.c — Week1 Day3-4: 構造体・qsort比較関数・関数ポインタ
 * make drill04 && ./drill04
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int failures = 0;
#define CHECK(name, cond) do { \
    if (cond) { printf("  PASS  %s\n", name); } \
    else      { printf("  FAIL  %s\n", name); failures++; } \
} while (0)

typedef struct {
    uint32_t id;
    char     name[16];
    float    temperature;
} Sensor;

/* 課題1: qsort用 id昇順の比較関数
 * ヒント: 戻り値は 負/0/正。a - b 形式はオーバーフローの罠があるので
 *         (x > y) - (x < y) のイディオムを推奨 */
int cmp_by_id(const void *a, const void *b) {
    (void)a; (void)b;         /* TODO */
    return 0;
}

/* 課題2: 温度の降順(高い順)の比較関数 */
int cmp_by_temp_desc(const void *a, const void *b) {
    (void)a; (void)b;         /* TODO */
    return 0;
}

/* 課題3: 全要素にコールバックを適用する(関数ポインタの練習) */
typedef void (*sensor_fn)(Sensor *s);
void for_each_sensor(Sensor *arr, size_t n, sensor_fn fn) {
    (void)arr; (void)n; (void)fn;   /* TODO */
}

/* コールバック実体(実装済み): 校正オフセット+0.5℃ */
static void calibrate(Sensor *s) { s->temperature += 0.5f; }

int main(void) {
    Sensor sensors[4] = {
        { 30, "s30", 25.0f },
        { 10, "s10", 27.5f },
        { 40, "s40", 22.0f },
        { 20, "s20", 26.0f },
    };

    puts("[cmp_by_id + qsort]");
    qsort(sensors, 4, sizeof(Sensor), cmp_by_id);
    CHECK("id昇順に並ぶ", sensors[0].id == 10 && sensors[1].id == 20 &&
                          sensors[2].id == 30 && sensors[3].id == 40);
    CHECK("nameも一緒に動く(構造体ごと入替)", strcmp(sensors[0].name, "s10") == 0);

    puts("[cmp_by_temp_desc + qsort]");
    qsort(sensors, 4, sizeof(Sensor), cmp_by_temp_desc);
    CHECK("温度降順", sensors[0].temperature > sensors[1].temperature &&
                      sensors[1].temperature > sensors[2].temperature &&
                      sensors[2].temperature > sensors[3].temperature);
    CHECK("先頭は27.5", sensors[0].temperature > 27.4f && sensors[0].temperature < 27.6f);

    puts("[for_each_sensor]");
    float before = sensors[0].temperature;
    for_each_sensor(sensors, 4, calibrate);
    CHECK("全要素に+0.5", sensors[0].temperature > before + 0.4f &&
                          sensors[0].temperature < before + 0.6f);

    if (failures == 0) { puts("\nALL PASS! 次: 教材 Week1 Day4(モジュール分割)へ"); return 0; }
    printf("\n%d 件 FAIL\n", failures);
    return 1;
}
