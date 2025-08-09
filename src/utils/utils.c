#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>


static char timeFormatted[50] = {0};

time_t UTILSstrToTstmp(const char * string){
    uint64_t day,month,year; 
    int n = sscanf(string, "%lu-%lu-%lu",&day,&month,&year);   
    if(n != 3) return 0;
    
    struct tm timeinfo = {0};
    timeinfo = (struct tm){
        .tm_mon = month-1,
        .tm_mday = day,
        .tm_year = year-1900
    };
    
    return mktime(&timeinfo);
}

time_t UTILStomorrow(void){
    time_t currTime = time(NULL);
    time_t oneDay = 86400;
    time_t tomorrow = (currTime/oneDay) * oneDay + oneDay ;
    return tomorrow;
} 

void UTILStstmpToString(uint64_t timestamp){
    time_t tstmp = (time_t)timestamp;
    struct tm *T = localtime(&tstmp);
    strftime(timeFormatted,sizeof(timeFormatted)/sizeof(char),"%d.%m.%Y",T);
}
 
char * UTILSgetDate(void){
    return timeFormatted;
}

uint64_t UTILShash(uint64_t x) {
    x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
    x = x ^ (x >> 31);
    return x;
}

static char encoded[50] = {0}; 
const char encTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char * UTILSenShittify(uint64_t number){
    //shitty base64 encoding
    uint64_t bitSize = sizeof(number) * 8;
    uint64_t index = 0;
    bool leading = true;
    
    
    for(int i = bitSize-6; i >= 0; i-=6){
        uint64_t toEncode = (number>>i) & 0x3F; 
        if(toEncode){
            leading = false;
        }
        if(leading) continue;
        encoded[index++] = encTable[toEncode]; 
    }
    encoded[index] = '\0';
    return encoded;
}

