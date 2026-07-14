#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "parse.h"

struct SensorLog{
    int *timestamp, *sensor_id, *value;
    size_t capacity, head, tail, count;
};

SensorLog *slog_create(size_t capacity){
    SensorLog* slog = malloc(sizeof(SensorLog));

    if (slog==NULL) return NULL;
    
    slog->timestamp = malloc(capacity * sizeof(slog->timestamp[0]));
    slog->sensor_id = malloc(capacity * sizeof(slog->sensor_id[0]));
    slog->value     = malloc(capacity * sizeof(slog->value[0]));

    if (slog->timestamp==NULL){
        free(slog);
        slog = NULL;
        return NULL;
    }
    if (slog->sensor_id==NULL){
        free(slog);
        slog = NULL;
        return NULL;
    }
    if (slog->value==NULL){
        free(slog);
        slog = NULL;
        return NULL;
    }

    slog->capacity = capacity;
    slog->head  = 0;
    slog->tail  = 0;
    slog->count = 0;

    return slog;
}

void slog_destroy(SensorLog *sl){
    if(sl == NULL) return;
    free(sl->timestamp);
    free(sl->sensor_id);
    free(sl->value);
    sl->capacity = 0;
    sl->head = 0;
    sl->tail = 0;
    sl->count = 0;
    free(sl);
}

void slog_push(SensorLog *sl, int ts, int id, int temp){
    if(sl->head == sl->capacity){
        size_t tmpcap = sl->capacity * 2;
        int *tmp_ti = realloc(sl->timestamp, tmpcap*sizeof(sl->timestamp[0]));
        int *tmp_si = realloc(sl->sensor_id, tmpcap*sizeof(sl->sensor_id[0]));
        int *tmp_vl = realloc(sl->value,     tmpcap*sizeof(sl->value[0]));
        if(tmp_ti!=NULL){
            sl->capacity = tmpcap;
            sl->timestamp = tmp_ti;
        }
        if(tmp_si!=NULL){
            sl->capacity = tmpcap;
            sl->sensor_id = tmp_si;
        }
        if(tmp_vl!=NULL){
            sl->capacity = tmpcap;
            sl->value = tmp_vl;
        }
    }
    
    sl->timestamp[sl->head] = ts;
    sl->sensor_id[sl->head] = id;
    sl->value[sl->head]     = temp;

    sl->head = sl->head + 1;
    
    if (sl->count != sl->capacity) sl->count++;
}

bool slog_pop(SensorLog *sl, int *ts, int *id, int *temp){
    if(sl->count == 0){
        return false;
    }
    *ts   = sl->timestamp[sl->tail];
    *id   = sl->sensor_id[sl->tail];
    *temp = sl->value[sl->tail];
    sl->tail = (sl->tail + 1) % sl->capacity;
    sl->count--;
    return true;
}

size_t    slog_count(const SensorLog *sl){
    return sl->count;
}