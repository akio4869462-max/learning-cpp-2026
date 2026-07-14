#ifndef COLLECT_H
#define COLLECT_H

#include <stdlib.h>
#include <stdio.h>

#include "parse.h"

void collect_stats(SensorLog *sl);
void collect_filter(SensorLog *sl, size_t win);
void collect_worst(SensorLog *sl);

#endif