#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void reverse(int *arr, size_t n);

int main(){
    int arr[] = {10, 20, 30, 40, 50};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    reverse(arr, size);

    for(size_t i=0;i<size;i++)
        printf("%d ",arr[i]);
    printf("\n");
    return 0;
}

void reverse(int *arr, size_t n){
    int *left = arr;
    int *right = arr + n - 1;

    while(left < right){
        int tmp = *left;
        *left = *right;
        *right = tmp;

        left++;
        right--;
    }
}