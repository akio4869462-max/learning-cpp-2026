#include "ringbuf.h"
#include <stdlib.h>

struct RingBuf {
    uint8_t *buf;
    size_t   capacity, head, tail, count;
};

RingBuf *ringbuf_create(size_t capacity){
    RingBuf* rbuf = malloc(sizeof(RingBuf));
    if (rbuf==NULL) return NULL;
    
    rbuf->buf = malloc(capacity * sizeof(uint8_t));
    if (rbuf->buf==NULL){
        free(rbuf);
        rbuf = NULL;
        return NULL;
    }

    rbuf->capacity = capacity;
    rbuf->head  = 0;
    rbuf->tail  = 0;
    rbuf->count = 0;

    return rbuf;
}

void ringbuf_destroy(RingBuf *rb){
    if(rb == NULL) return;
    free(rb->buf);
    rb->buf = NULL;
    rb->capacity = 0;
    rb->count = 0;
    rb->head = 0;
    rb->tail = 0;
    free(rb);
}

bool ringbuf_push(RingBuf *rb, uint8_t byte){
    if(rb->count == rb->capacity){
        return false;
    }
    rb->buf[rb->head] = byte;
    rb->head = (rb->head + 1) % rb->capacity;
    rb->count++;
    return true;
}

bool ringbuf_pop(RingBuf *rb, uint8_t *out){
    if(rb->count == 0){
        return false;
    }
    *out = rb->buf[rb->tail];
    rb->tail = (rb->tail + 1) % rb->capacity;
    rb->count--;
    return true;
}

size_t ringbuf_count(const RingBuf *rb){
    return rb->count;
}