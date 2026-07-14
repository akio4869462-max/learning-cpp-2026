#ifndef PARSE_H
#define PARSE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



typedef struct SensorLog SensorLog;

SensorLog *slog_create(size_t capacity);
void       slog_destroy(SensorLog *sl);
void       slog_push(SensorLog *sl, int ts, int id, int temp);
bool       slog_pop(SensorLog *sl, int *ts, int *id, int *temp);
size_t     slog_count(const SensorLog *sl);

#endif