#include "stack.h"
#include <stdlib.h>

void init(Stack *s, size_t capacity){
    s->arr = malloc(capacity * sizeof(s->arr[0]));
    if(s->arr==NULL){
        s->capacity = 0;
        s->size =0;
        return;
    }
    s->capacity = capacity;
    s->size = 0;
}

void push(Stack *s, int data){
    if(s->size==s->capacity){
        resize(s);
        if (s->size == s->capacity) {
            return;   // resize失敗
        }
    }
    s->arr[s->size] = data;
    s->size++;
}

void pop(Stack *s){
    if(s->size > 0) s->size--;
}

void resize(Stack *s){
    size_t tmpcap = s->capacity * 2;
    int *tmp = realloc(s->arr, tmpcap*sizeof(s->arr[0]));
    if(tmp!=NULL){
        s->capacity = tmpcap;
        s->arr = tmp;
    }
}

void destroy(Stack *s){
    free(s->arr);
    s->arr = NULL;
    s->size = 0;
    s->capacity = 0;
}