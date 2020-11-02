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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <klimalogglib.h>

int main(int argc, char *argv[]) {

    // We only care about a single filepath
    if (argc != 2) {
        printf("Usage:\tparsefile [filepath]");
        return 0;
    }

    uint32_t counter = 0;

    // try opening the file
    FILE *file;
    file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Error opening file!");
        return 1;
    }

    // make a buffer for storing a single entry
    uint8_t *buffer = malloc(KLG_MEASURE_SIZE);
    while(1) {
        // read a fixed amount of data
        size_t read = fread(buffer, 1, KLG_MEASURE_SIZE, file);
        // stop when there's nothing more to read (even if data cuts off)
        if (read != KLG_MEASURE_SIZE) break;

        // parse the read data
        struct klg_measurement measurement;
        klg_parsebuffer(&measurement, buffer, sizeof(buffer));

        // Print formatted timestamp
        printf("%u-%02u-%02u %02u:%02u:%02u ",
                measurement.datetime.tm_year+1900,
                measurement.datetime.tm_mon+1,
                measurement.datetime.tm_mday,
                measurement.datetime.tm_hour,
                measurement.datetime.tm_min,
                measurement.datetime.tm_sec);

        // For every connected sensor check if it's active (and if data is in range)
        // print out the parsed data
        if (measurement.sensor0.t_enable || measurement.sensor0.h_enable) {
            printf("[0] ");
            if (measurement.sensor0.t_enable) printf("T:%.2fC ", measurement.sensor0.temp);
            if (measurement.sensor0.h_enable) printf("H:%.2f%% ", measurement.sensor0.humid);
        }
        if (measurement.sensor1.t_enable || measurement.sensor1.h_enable) {
            printf("[1] ");
            if (measurement.sensor1.t_enable) printf("T:%.2fC ", measurement.sensor1.temp);
            if (measurement.sensor1.h_enable) printf("H:%.2f%% ", measurement.sensor1.humid);
        }
        if (measurement.sensor2.t_enable || measurement.sensor2.h_enable) {
            printf("[2] ");
            if (measurement.sensor2.t_enable) printf("T:%.2fC ", measurement.sensor2.temp);
            if (measurement.sensor2.h_enable) printf("H:%.2f%% ", measurement.sensor2.humid);
        }
        if (measurement.sensor3.t_enable || measurement.sensor3.h_enable) {
            printf("[3] ");
            if (measurement.sensor3.t_enable) printf("T:%.2fC ", measurement.sensor3.temp);
            if (measurement.sensor3.h_enable) printf("H:%.2f%% ", measurement.sensor3.humid);
        }
        if (measurement.sensor4.t_enable || measurement.sensor4.h_enable) {
            printf("[4] ");
            if (measurement.sensor4.t_enable) printf("T:%.2fC ", measurement.sensor4.temp);
            if (measurement.sensor4.h_enable) printf("H:%.2f%% ", measurement.sensor4.humid);
        }
        if (measurement.sensor5.t_enable || measurement.sensor5.h_enable) {
            printf("[5] ");
            if (measurement.sensor5.t_enable) printf("T:%.2fC ", measurement.sensor5.temp);
            if (measurement.sensor5.h_enable) printf("H:%.2f%% ", measurement.sensor5.humid);
        }
        if (measurement.sensor6.t_enable || measurement.sensor6.h_enable) {
            printf("[6] ");
            if (measurement.sensor6.t_enable) printf("T:%.2fC ", measurement.sensor6.temp);
            if (measurement.sensor6.h_enable) printf("H:%.2f%% ", measurement.sensor6.humid);
        }
        if (measurement.sensor7.t_enable || measurement.sensor7.h_enable) {
            printf("[7] ");
            if (measurement.sensor7.t_enable) printf("T:%.2fC ", measurement.sensor7.temp);
            if (measurement.sensor7.h_enable) printf("H:%.2f%% ", measurement.sensor7.humid);
        }
        if (measurement.sensor8.t_enable || measurement.sensor8.h_enable) {
            printf("[8] ");
            if (measurement.sensor8.t_enable) printf("T:%.2fC ", measurement.sensor8.temp);
            if (measurement.sensor8.h_enable) printf("H:%.2f%% ", measurement.sensor8.humid);
        }

        if (measurement.sensor0.alarm) printf("A0 ");
        if (measurement.sensor1.alarm) printf("A1 ");
        if (measurement.sensor2.alarm) printf("A2 ");
        if (measurement.sensor3.alarm) printf("A3 ");
        if (measurement.sensor4.alarm) printf("A4 ");
        if (measurement.sensor5.alarm) printf("A5 ");
        if (measurement.sensor6.alarm) printf("A6 ");
        if (measurement.sensor7.alarm) printf("A7 ");
        if (measurement.sensor8.alarm) printf("A8 ");

        printf("\n");
        counter++;
    }
    
    // cleanup
    free(buffer);
    fclose(file);
    printf("READ: %u\n", counter);
    return 0;
}