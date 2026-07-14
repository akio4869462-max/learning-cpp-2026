#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "filter.h"

int main(){
    Filter *fil = filter_create(5);

    float mean;

    bool mean_ok = filter_mean(fil, &mean);
    printf("中身がないときの移動平均: %s\n", mean_ok ? "成功(NG)" : "失敗(OK)");
    
    filter_push(fil, 15.0);
    filter_push(fil, 20.0);
    filter_push(fil, 28.0);
    filter_push(fil, 10.0);
    filter_push(fil, 17.0);
    
    filter_mean(fil, &mean);
    printf("%f\n", mean);

    filter_push(fil, 25.0);
        
    filter_mean(fil, &mean);
    printf("%f\n", mean);
    
    filter_destroy(fil);

    return 0;
}
