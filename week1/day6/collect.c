#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "collect.h"
#include "filter.h"

typedef struct {
    int id;
    int min, max, sum, count;   // このIDの集計用
    int anomaly_count;          // このIDの異常値の件数
} IdStat;

typedef struct {
    int id;
    Filter *filter;
} FilterEntry;

static IdStat *find_or_create(IdStat **arr, size_t *count, size_t *capacity, int id);
static Filter *get_filter(FilterEntry **arr, size_t *count, size_t *capacity, int id, size_t win);

void collect_stats(SensorLog *sl){
    IdStat *arr = NULL;
    size_t  count = 0;
    size_t  capacity = 0;
    int ts, id, temp;
    
    while(slog_pop(sl, &ts, &id, &temp)){
        IdStat *stat = find_or_create(&arr, &count, &capacity, id);
        if(temp == -999){
            stat->anomaly_count++;
        }else{
            if(stat->min > temp) stat->min = temp;
            if(stat->max < temp) stat->max = temp;
            stat->sum += temp;
            stat->count++;
        }
    }
    for(size_t i=0;i<count;i++){
        if(arr[i].count!=0)
            printf("id: %d, min: %d, max: %d, ave: %.2f, anomaly: %d\n", (arr[i]).id, arr[i].min, arr[i].max, (float)(arr[i].sum) / (float)(arr[i].count), arr[i].anomaly_count);
    }
    free(arr);
}

void collect_filter(SensorLog *sl, size_t win){
    FilterEntry *arr = NULL;
    size_t  count = 0;
    size_t  capacity = 0;
    int ts, id, temp;
    float mean;

    printf("timestamp, sensor_id, mean\n");
    while(slog_pop(sl, &ts, &id, &temp)){
        if(temp == -999){
            continue;
        }else{
            Filter *fil = get_filter(&arr, &count, &capacity, id, win);
            filter_push(fil, (float)temp);
            if(filter_mean(fil,&mean)){
                printf("%d,%d,%.2f\n", ts, id, mean);
            }
        }
    }
    for(size_t i=0;i<count;i++){
        filter_destroy(arr[i].filter);
    }
    free(arr);
}

void collect_worst(SensorLog *sl){
    IdStat *arr = NULL;
    size_t  count = 0;
    size_t  capacity = 0;
    int ts, id, temp;

    while(slog_pop(sl, &ts, &id, &temp)){
        IdStat *stat = find_or_create(&arr, &count, &capacity, id);
        if(temp == -999){
            stat->anomaly_count++;
        }else{
            stat->count++;
        }
    }

    int worst_id = -1;
    float worst_rate = -1.0f;
    for(size_t i=0;i<count;i++){
        int total = arr[i].count + arr[i].anomaly_count;
        float rate = (float)(arr[i].anomaly_count) / (float)total;

        if(rate > worst_rate){
            worst_rate = rate;
            worst_id = arr[i].id;
        }
    }

    if(worst_id == -1){
        printf("データがありません\n");
    }else{
        printf("worst_id: %d (anomaly rate: %.2f%%)\n", worst_id, worst_rate * 100);
    }

    free(arr);
}

static IdStat *find_or_create(IdStat **arr, size_t *count, size_t *capacity, int id){
    for(size_t i=0;i<*count;i++){
        if((*arr)[i].id == id){
            return (&(*arr)[i]);
        }
    }
    IdStat *tmp_arr;
    tmp_arr = *arr;
    if(*capacity==0){
        *capacity = 4;
        tmp_arr = realloc(*arr, (*capacity)*sizeof(*arr[0]));
    }else if(*count == *capacity){
        size_t tmpcap = (*capacity) * 2;
        tmp_arr = realloc(*arr, tmpcap*sizeof(*arr[0]));
    }
    if(tmp_arr!=NULL){
        *arr = tmp_arr;
    }
    (*arr)[*count].id = id;
    (*arr)[*count].min = INT_MAX;
    (*arr)[*count].max = INT_MIN;
    (*arr)[*count].sum = 0;
    (*arr)[*count].count = 0;
    (*arr)[*count].anomaly_count = 0;
    
    (*count)++;

    return (&(*arr)[*count-1]);
}

static Filter *get_filter(FilterEntry **arr, size_t *count, size_t *capacity, int id, size_t win){
    for(size_t i=0;i<*count;i++){
        if((*arr)[i].id == id){
            return (*arr)[i].filter;
        }
    }
    FilterEntry *tmp_arr;
    tmp_arr = *arr;
    if(*capacity==0){
        *capacity = 4;
        tmp_arr = realloc(*arr, (*capacity)*sizeof(*arr[0]));
    }else if(*count == *capacity){
        size_t tmpcap = (*capacity) * 2;
        tmp_arr = realloc(*arr, tmpcap*sizeof(*arr[0]));
    }
    if(tmp_arr!=NULL){
        *arr = tmp_arr;
    }
    (*arr)[*count].id = id;
    (*arr)[*count].filter = filter_create(win);
    
    (*count)++;

    return ((*arr)[*count-1].filter);
}