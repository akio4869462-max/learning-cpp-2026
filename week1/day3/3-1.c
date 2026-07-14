#include <stdlib.h>
#include <stdio.h>

int *make_array_bad(size_t n);
int *make_array(size_t n);

int main(){
    // 呼び出し側の責務
    int *arr = make_array(10);

    if(arr == NULL) return 1;
    
    for (size_t i = 0; i < 10; i++) {
        arr[i] = (int)i;
        printf("%d ", arr[i]);
    
    }
    printf("\n");
    
    if (arr) {
        /* 使う */
        free(arr);       // 確保した者が解放する(所有権の考え方。C++のRAIIへ繋がる)
        arr = NULL;      // 解放後にNULL代入(二重free・use-after-free防止の習慣)
        // printf("%d\n", arr[0]);
    }

    return 0;
}

// int *make_array_bad(size_t n) {
//     int a[n];
//     return a;        // ★禁止: ローカル変数は関数を出ると消える(ダングリングポインタ)
// }

int *make_array(size_t n) {
    int *a = malloc(n * sizeof(int));   // ヒープ確保(生存期間は自分で管理)
    if (a == NULL) return NULL;          // 確保失敗チェックは必須
    return a;
}
