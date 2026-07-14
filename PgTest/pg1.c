#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool second_largest(const int *arr, size_t n, int *out);

int main(){
    int ans;

    printf("-------test1-------\n");
    int arr1[] = {1,3,4,2,5};

    if(second_largest(arr1, sizeof(arr1)/sizeof(arr1[0]), &ans)){
        printf("answer: %d\n", ans);
    }else{
        printf("配列の要素数が2未満です。\n");
    }

    printf("-------test2-------\n");
    int arr2[] = {1};

    if(second_largest(arr2, sizeof(arr2)/sizeof(arr2[0]), &ans)){
        printf("answer: %d\n", ans);
    }else{
        printf("配列の要素数が2未満です。\n");
    }

    printf("-------test3-------\n");
    int arr3[] = {3,3,3,2,2};

    if(second_largest(arr3, sizeof(arr3)/sizeof(arr3[0]), &ans)){
        printf("answer: %d\n", ans);
    }else{
        printf("配列の要素数が2未満です。\n");
    }

    return 0;
}

//重複値の扱い(今回は「許容して2番目に大きい"位置"を返す」という仕様)
bool second_largest(const int *arr, size_t n, int *out){
    int first = INT_MIN + 1;
    int second = INT_MIN;
    if(n<2){
        return false;
    }else{
        for(size_t i = 0;i<n;i++){
            if(first<arr[i]){
                second = first;
                first = arr[i];
            }else if(second<arr[i]){
                second = arr[i];
            }
        }
        *out = second;
        return true;
    }
}