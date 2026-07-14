#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef void (*callback_t)(uint32_t event);

void on_rx(uint32_t event) { printf("rx: %u\n", event); }

int cmp_int(const void *a, const void *b) {
    return (*(const int *)a > *(const int *)b) - (*(const int *)a < *(const int *)b);
}

int main(){
    // 登録して後で呼ぶ(割り込みハンドラ登録・ドライバのops構造体はこの形)
    callback_t handler = on_rx;
    handler(42);

    int arr[] = {5, 2, 4, 1, 3};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    
    // qsortの比較関数もコールバック
    qsort(arr, n, sizeof(int), cmp_int);

    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}