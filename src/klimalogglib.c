/*
    KlimaLoggLib - KlimaLoggPro data manipulation library
    Copyright (C) 2020  Nexrem

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <time.h>
#include <string.h>
#include <stdint.h>
#include <klimalogglib.h>

void klg_getdatetime(struct tm *_datetime, uint64_t _timestamp) {
    // subtract unixtime in julian from the timestamp and get to seconds
    time_t epoch = (_timestamp-KLG_UNIX_T_JULIAN)/1000000;
    struct tm *normalized_time = gmtime(&epoch);
    memcpy(_datetime, normalized_time, sizeof(struct tm));
}

uint64_t klg_gettimestamp(struct tm *_datetime) {
    // get epoch from datetime, turn into micros and add unixtime in julian
    time_t epoch = mktime(_datetime);
    uint64_t timestamp = (epoch*1000000)+KLG_UNIX_T_JULIAN;
    return timestamp;
}

float klg_gettemp(uint32_t _temp) {
    float temperature;
    memcpy(&temperature, &_temp, sizeof(_temp));
    return temperature;
}

float klg_gethumid(uint32_t _humi) {
    float humidity;
    memcpy(&humidity, &_humi, sizeof(_humi));
    return humidity;
}

int8_t klg_parsebuffer(struct klg_measurement* _measurement, uint8_t *_buf, size_t size) {
    // not enough data in buffer to read
    if (size<KLG_MEASURE_SIZE) return 1;
    
    // measurement data is little-endian, flip byte order and merge
    size_t index = 0;
    uint64_t timestamp = 0;
    for (int i=0;i<8;i++) {
        uint64_t data = *(_buf+index);
        timestamp |= data<<(i*8);
        index++;
    }

    // Read the alarm flags (bytes 80 and 81)
    uint16_t alarm = *(_buf+80) | *(_buf+81)<<8;

    // convert parsed time
    klg_getdatetime(&_measurement->datetime, timestamp);

    // Read sensordata for all 1+8 sensors
    for (uint8_t i=0;i<9;i++) {

        uint32_t temp = 0;
        uint32_t humid = 0;

        // Select sensor
        struct klg_sensordata *sensor_p;
        switch(i) {
            case 0:
                sensor_p = &_measurement->sensor0;
                break;
            case 1:
                sensor_p = &_measurement->sensor1;
                break;
            case 2:
                sensor_p = &_measurement->sensor2;
                break;
            case 3:
                sensor_p = &_measurement->sensor3;
                break;
            case 4:
                sensor_p = &_measurement->sensor4;
                break;
            case 5:
                sensor_p = &_measurement->sensor5;
                break;
            case 6:
                sensor_p = &_measurement->sensor6;
                break;
            case 7:
                sensor_p = &_measurement->sensor7;
                break;
            case 8:
                sensor_p = &_measurement->sensor8;
                break;
        }

        // Flip byte order of temp reading
        for (uint8_t j=0;j<4;j++) {
            uint32_t data = *(_buf+index);
            temp |= data<<(j*8);
            index++;
        }

        // Flip byte order of humidity reading
        for (uint8_t j=0;j<4;j++) {
            uint32_t data = *(_buf+index);
            humid |= data<<(j*8);
            index++;
        }

        // Set enable flags and write data out
        if (temp == KLG_INVALID_TEMP) {
            sensor_p->t_enable = 0;
        }
        else {
            sensor_p->t_enable = 1;
            memcpy(&sensor_p->temp, &temp, sizeof(temp));
        }

        // Set enable flags and write data out
        if (humid == KLG_INVALID_HUMID) {
            sensor_p->h_enable = 0;
        }
        else {
            sensor_p->h_enable = 1;
            memcpy(&sensor_p->humid, &humid, sizeof(humid));
        }

        sensor_p->alarm = (alarm & (1<<i)) ? 1 : 0;
    }
    return 0;
}