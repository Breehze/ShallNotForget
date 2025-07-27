#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>


static char timeFormatted[50] = {0};

size_t strToTstmp(const char * string){
    size_t day,month,year; 
    int n = sscanf(string, "%ld-%ld-%ld",&day,&month,&year);   
    if(n != 3) return -1;
    
    struct tm timeinfo = {0};
    timeinfo = (struct tm){
        .tm_mon = month-1,
        .tm_mday = day,
        .tm_year = year-1900
    };
    
    return mktime(&timeinfo);
}

void tstmpToString(size_t timestamp){
    time_t tstmp = (time_t)timestamp;
    struct tm *T = localtime(&tstmp);
    strftime(timeFormatted,sizeof(timeFormatted)/sizeof(char),"%d.%m.%Y",T);
}
 
char * getDate(){
    return timeFormatted;
}

uint64_t hash(uint64_t x) {
    x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
    x = x ^ (x >> 31);
    return x;
}

static char encoded[50] = {0}; 
const char encTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char * enShittify(size_t number){
    //shitty base64 encoding
    size_t bitSize = sizeof(number) * 8;
    size_t paddingSize = bitSize % 6;
    size_t index = 0;
    bool leading = true;
    
    
    for(int i = bitSize-6; i >= 0; i-=6){
        size_t toEncode = (number>>i) & 0x3F; 
        if(toEncode){
            leading = false;
        }
        if(leading) continue;
        encoded[index++] = encTable[toEncode]; 
    }
    encoded[index] = '\0';
    return encoded;
}

