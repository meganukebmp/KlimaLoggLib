#ifndef KLIMALOGGLIB_H
#define KLIMALOGGLIB_H

#include <time.h>

#define KLG_INVALID_TEMP    0x42A23333
#define KLG_INVALID_HUMID   0x42DC0000
#define KLG_UNIX_T_JULIAN   210866803200000000
#define KLG_MEASURE_SIZE    84

struct klg_sensordata {
    uint8_t t_enable;
    uint8_t h_enable;
    float temp;
    float humid;
};

struct klg_measurement{
    struct tm datetime;
    struct klg_sensordata sensor0;
    struct klg_sensordata sensor1;
    struct klg_sensordata sensor2;
    struct klg_sensordata sensor3;
    struct klg_sensordata sensor4;
    struct klg_sensordata sensor5;
    struct klg_sensordata sensor6;
    struct klg_sensordata sensor7;
    struct klg_sensordata sensor8;
};

void klg_getdatetime(struct tm *_datetime, uint64_t _timestamp);
uint64_t klg_gettimestamp(struct tm *_datetime);
float klg_gettemp(uint32_t _temp);
float klg_gethumi(uint32_t _humi);
int8_t klg_parsebuffer(struct klg_measurement* _measurement, uint8_t *_buf, size_t _size);

#endif // KLIMALOGGLIB_H