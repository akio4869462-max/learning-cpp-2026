#include <stdlib.h>
#include <stdio.h>

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

int main(){
    Stack s;

    init(&s, 4);
    
    push(&s,10);
    push(&s,20);
    push(&s,30);

    for(size_t i=0;i<s.size;i++){
        printf("%d ",s.arr[i]);
    }
    printf("\n");

    destroy(&s);

    return 0;
}

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