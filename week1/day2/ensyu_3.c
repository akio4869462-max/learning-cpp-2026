#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int find(const int *arr, size_t n, int target);

int main(){
    int arr[] = {10, 20, 30, 40, 50};
    
    find(arr, 5, 30);
    size_t n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", find(arr, n, 30));  // 2になるはず
    printf("%d\n", find(arr, n, 99));  // -1になるはず

    return 0;
}

// 配列の内容を変更せず、検索だけを行うため const を付ける
int find(const int *arr, size_t n, int target){
    for(size_t i=0;i<n;i++){
        if(arr[i] == target)
            return (int)i;
    }
    return -1;
}