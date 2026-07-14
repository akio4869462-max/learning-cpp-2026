#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int cmp_sensor_id(const void *a, const void *b);
int cmp_sensor_temp(const void *a, const void *b);

typedef struct {
    uint32_t id;
    char name[32];
    float temperature;
} Sensor;

int main(void)
{
    Sensor sensors[] = {
        {3, "C", 20.5},
        {1, "A", 30.0},
        {2, "B", 25.0},
    };

    size_t n = sizeof(sensors) / sizeof(sensors[0]);

    for(size_t i=0;i<n;i++){
        printf("%d %s %.1f", sensors[i].id, sensors[i].name, sensors[i].temperature);
        printf("\n");
    }
    
    // qsortの比較関数もコールバック
    
    printf("IdSort\n");
    qsort(sensors, n, sizeof(Sensor), cmp_sensor_id);

    for(size_t i=0;i<n;i++){
        printf("%d %s %.1f", sensors[i].id, sensors[i].name, sensors[i].temperature);
        printf("\n");
    }

    printf("TempSort\n");
    qsort(sensors, n, sizeof(Sensor), cmp_sensor_temp);

    for(size_t i=0;i<n;i++){
        printf("%d %s %.1f", sensors[i].id, sensors[i].name, sensors[i].temperature);
        printf("\n");
    }
    return 0;
}

int cmp_sensor_id(const void *a, const void *b){
    const Sensor *sa = (const Sensor *)a;
    const Sensor *sb = (const Sensor *)b;
    return (sa->id > sb->id) - (sa->id < sb->id);
}

int cmp_sensor_temp(const void *a, const void *b){
    const Sensor *sa = (const Sensor *)a;
    const Sensor *sb = (const Sensor *)b;
    return (sa->temperature > sb->temperature) - (sa->temperature < sb->temperature);
}