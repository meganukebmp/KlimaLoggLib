#include <cstdio>
#include <cstdint>


void printDate(uint64_t _date) {
    printf("%llu\n", _date);
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
        
        if (c == EOF) break;
        
        printDate(date);
        
        fseek(file, 76, SEEK_CUR);
    }
    
    fclose(file);
    printf("\n");
    return 0;
}