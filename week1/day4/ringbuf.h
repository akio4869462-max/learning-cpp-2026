#ifndef RINGBUF_H
#define RINGBUF_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct RingBuf RingBuf;

RingBuf *ringbuf_create(size_t capacity);
void     ringbuf_destroy(RingBuf *rb);
bool     ringbuf_push(RingBuf *rb, uint8_t byte);
bool     ringbuf_pop(RingBuf *rb, uint8_t *out);
size_t   ringbuf_count(const RingBuf *rb);

#endif