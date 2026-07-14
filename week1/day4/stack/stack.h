#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct {
    int *arr;        // データを格納する配列
    size_t size;     // 現在入っている要素数
    size_t capacity; // 配列の容量
} Stack;

void init(Stack *s, size_t capacity);
void push(Stack *s, int data);
void pop(Stack *s);
void resize(Stack *s);
void destroy(Stack *s);

#endif