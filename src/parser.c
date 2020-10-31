#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

// struct measurement {
//     tm datetime;
//     float temp0;
//     float humi0;
//     float temp1;
//     float humi1;
//     float temp2;
//     float humi2;
//     float temp3;
//     float humi3;
//     float temp4;
//     float humi4;
//     float temp5;
//     float humi5;
//     float temp6;
//     float humi6;
//     float temp7;
//     float humi7;
//     float temp8;
//     float humi8;
// };

void printDate(uint64_t _datetime) {
    // subtract unixtime in julian from our current time and divide to get to scale
    time_t thetime = (_datetime-210866803200000000)/1000000;
    struct tm *newtime = gmtime(&thetime);

    //printf("%s\n", asctime(localtime(&newtime)));
    printf("%u-%02u-%02u %02u:%02u:%02u ", newtime->tm_year+1900, newtime->tm_mon+1, newtime->tm_mday, newtime->tm_hour, newtime->tm_min, newtime->tm_sec);
}

uint64_t timefromunix(time_t t) {
    uint64_t newtime = (t*1000000)+210866803200000000;
    return newtime;
}

int main() {
    FILE *file;
   
    file = fopen("0_history.dat", "rb");
    
    while(1) {
        
        uint64_t date = 0;
        uint64_t c = 0;
        for (int i=0;i<8;i++) {
            c = fgetc(file);
            if (c == EOF) break;
            date |= c<<(i*8);
        }

        uint32_t humid = 0;
        for (int i=0;i<4;i++) {
            c = fgetc(file);
            if (c == EOF) break;
            humid |= c<<(i*8);
        }
        
        if (c == EOF) break;
        
        float humidf;
        memcpy(&humidf, &humid, sizeof(humidf));

        printDate(date);
        printf("%.1f\n", humidf);
        break;
        fseek(file, 72, SEEK_CUR);
    }
    
    fclose(file);
    printf("\n");
    return 0;
}