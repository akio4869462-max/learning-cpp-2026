#include "filter.h"
#include <stdlib.h>

struct Filter {
    float   *tempBuf;
    size_t   capacity, pos, count;
};

Filter *filter_create(size_t capacity){
    Filter* filBuf = malloc(sizeof(Filter));
    if (filBuf==NULL) return NULL;
    
    filBuf->tempBuf = malloc(capacity * sizeof(float));
    if (filBuf->tempBuf==NULL){
        free(filBuf);
        filBuf = NULL;
        return NULL;
    }

    filBuf->capacity = capacity;
    filBuf->pos      = 0;
    filBuf->count    = 0;

    return filBuf;
}

void filter_destroy(Filter *fil){
    if(fil == NULL) return;
    free(fil->tempBuf);
    fil->tempBuf = NULL;
    fil->capacity = 0;
    fil->count = 0;
    fil->pos = 0;
    free(fil);
}

void filter_push(Filter *fil, float temp){
    fil->tempBuf[fil->pos] = temp;
    fil->pos = (fil->pos + 1) % fil->capacity;
    
    if (fil->count != fil->capacity) fil->count++;
}

bool filter_mean(const Filter *fil, float *mean){
    if(fil->count == 0){
        return false;
    }
    float sum=0.0;
    for(size_t i=0;i<fil->count;i++){
        sum += fil->tempBuf[i];
    }

    *mean = sum / (float)fil->count;
    
    return true;
}

size_t filter_count(const Filter *fil){
    return fil->count;
}