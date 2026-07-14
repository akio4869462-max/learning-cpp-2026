#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint32_t id;
    char name[32];
    float temperature;
} Sensor;

typedef struct {
    char c;
    uint32_t id;
    char d;
} Example;

void print_sensor(const Sensor *s);

int main(void)
{
    Sensor s = { .id = 1, .name = "temp0", .temperature = 25.5f };

    print_sensor(&s);

    printf("%zu\n", sizeof(Example));
    printf("sizeof(Sensor) = %zu\n", sizeof(Sensor));
    printf("members total  = %zu\n",
           sizeof(s.id) + sizeof(s.name) + sizeof(s.temperature));

    return 0;
}

void print_sensor(const Sensor *s)
{
    printf("%u %s %.1f\n", s->id, s->name, s->temperature);
}