#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "ringbuf.h"

int main(){
    RingBuf *rb = ringbuf_create(1);

    uint8_t out;

    bool pop_ok = ringbuf_pop(rb, &out);
    printf("中身がないときのpop: %s\n", pop_ok ? "成功(NG)" : "失敗(OK)");
    
    ringbuf_push(rb, 1);
    
    bool push_ok = ringbuf_push(rb, 2);   // 容量5に対して6個目
    printf("2個目のpush: %s\n", push_ok ? "成功(NG)" : "失敗(OK)");
    
    ringbuf_pop(rb, &out);
    printf("%d\n", out);
    
    pop_ok = ringbuf_pop(rb, &out);
    printf("2回目のpop: %s\n", pop_ok ? "成功(NG)" : "失敗(OK)");

    ringbuf_destroy(rb);

    return 0;
}
