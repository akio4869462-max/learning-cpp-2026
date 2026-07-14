#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

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
