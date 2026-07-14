#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "ringbuf.h"
#include "filter.h"

static uint8_t round_clip(float temp);

int main(){
    RingBuf *rb = ringbuf_create(5);
    Filter *fil = filter_create(5);

    float temp_buf[] = {10.0, 11.0, 12.0, 13.0, 14.0};

    size_t buf_size = sizeof(temp_buf) / sizeof(float);

    for(size_t i = 0;i<buf_size;i++){
        filter_push(fil, temp_buf[i]);
    }
    float mean;
    filter_mean(fil, &mean);
    
    uint8_t rmean = round_clip(mean);

    ringbuf_push(rb, rmean);

    uint8_t out;

    ringbuf_pop(rb, &out);

    printf("%d\n", out);

    ringbuf_destroy(rb);
    filter_destroy(fil);

    return 0;
}

static uint8_t round_clip(float temp){
    uint8_t rtemp;
    
    if(temp > 255) temp = 255;
    if(temp < 0)   temp =   0;
    
    rtemp = (uint8_t)roundf(temp);

    return rtemp;
}