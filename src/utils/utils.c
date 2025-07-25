#include <string.h>
#include <stdio.h>
#include <time.h>


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
