#ifndef FILTER_H
#define FILTER_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct Filter Filter;

Filter  *filter_create(size_t capacity);
void     filter_destroy(Filter *fil);
void     filter_push(Filter *fil, float temp);
bool     filter_mean(const Filter *fil, float *mean);
size_t   filter_count(const Filter *fil);

#endif