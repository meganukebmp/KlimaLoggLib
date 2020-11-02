/*
    KlimaLoggLib - KlimaLoggPro data manipulation library
    Copyright (C) 2020  Nexrem

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef KLIMALOGGLIB_H
#define KLIMALOGGLIB_H

#include <time.h>

#define KLG_INVALID_TEMP    0x42A23333
#define KLG_INVALID_HUMID   0x42DC0000
#define KLG_UNIX_T_JULIAN   210866803200000000
#define KLG_MEASURE_SIZE    84

// individual sensor data
struct klg_sensordata {
    uint8_t t_enable;
    uint8_t h_enable;
    uint8_t alarm;
    float temp;
    float humid;
};

// A whole measurement (encompassing many sensors)
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

// converts a device formatted timestamp into a C tm structure
void klg_getdatetime(struct tm *_datetime, uint64_t _timestamp);
// converts a tm structure into a device formatted timestamp
uint64_t klg_gettimestamp(struct tm *_datetime);
// converts device formatted temperature to a float
float klg_gettemp(uint32_t _temp);
// converts a device formatted humidity to a float
float klg_gethumi(uint32_t _humi);
// converts a buffer of data and writes to a klg_measurement structure (single measurement)
// returns 0 on success or a nonzero error code
int8_t klg_parsebuffer(struct klg_measurement* _measurement, uint8_t *_buf, size_t _size);

#endif // KLIMALOGGLIB_H