#include <jansson.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

#include "ops.h"
#include "fsops.h"

char timeFormatted[50] = {0};

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

void snfAdd(const char * reminder,const char * timestamp){
    size_t timestampOG = strToTstmp(timestamp) ;
    if(timestampOG == -1) return;
    
    json_t * root = FSopenJson();

    if(!root || !json_is_array(root)){
        printf("No workey\n");
        json_decref(root);
        return;
    }
    
    size_t index = 0;
    json_t * value;
    json_array_foreach(root, index, value){
        if(!json_is_object(value)) return;
        
        json_t * timestampAcc = json_object_get(value,"timestamp");
        
        if(!json_is_integer(timestampAcc)) return;

        size_t tmstp = json_number_value(timestampAcc);
        
        if(timestampOG < tmstp){
            break; 
        }
    }

    json_t * newRecord = json_object(); 
    json_object_set_new(newRecord,"timestamp",json_integer(timestampOG));
    json_object_set_new(newRecord,"data",json_string(reminder));
    
    json_array_insert(root,index,newRecord);
    
    FSdumpJson(root);
    
    json_decref(root);
    json_decref(newRecord);
    return;
}

void snfFindFromTimestamp(size_t timestamp,size_t bound){
    
    json_t * root = FSopenJson();   
    
    if(!root || !json_is_array(root)){
        json_decref(root);
        return;
    } 
    
    //do some fancy bin search here eventually 
    size_t index = 0;
    json_t *value;
    
    json_array_foreach(root,index,value){
        if(!json_is_object(value)){
            index = -1;
            break;
        }

        json_t * jsonTimestamp = json_object_get(value,"timestamp");
        if(!json_is_number(jsonTimestamp)){
            index = -1;         
            break;
        }
        if(json_integer_value(jsonTimestamp) > timestamp){
            break;
        }
    }
    
    for(size_t i = index; i < index+bound;i++){
        json_t * jobj = json_array_get(root,i);
        
        if(!jobj || !json_is_object(jobj)){
            break;
        }
        
        json_t *jtimestamp = json_object_get(jobj,"timestamp");
        json_t *jdata = json_object_get(jobj,"data"); 

        if(!json_is_number(jtimestamp) || !json_is_string(jdata)){
            break;
        }

        const char * data = json_string_value(jdata);
        size_t ts = json_integer_value(jtimestamp);
        
        size_t dayDiff = (ts-timestamp)/(3600*24);
        tstmpToString(ts);
        printf("%s in %ld days | %s \n",timeFormatted,dayDiff,data);

    }

    json_decref(root);
}
