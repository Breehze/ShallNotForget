#include <jansson.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "ops.h"
#include "../fsops/fsops.h"
#include "../utils/utils.h"

void snfAdd(const char * reminder,const char * timestamp){
    time_t timestampOG = 0;
    if(strcmp(timestamp,"tomorrow") == 0){
        timestampOG = UTILStomorrow();
    }else{
        timestampOG = UTILSstrToTstmp(timestamp);
    }
    
    if(timestampOG == 0) return;
    json_t * root = FSopenJson();

    if(!root || !json_is_array(root)){
        printf("No workey\n");
        json_decref(root);
        return;
    }
    
    uint64_t index = 0;
    json_t * value;
    json_array_foreach(root, index, value){
        if(!json_is_object(value)) return;
        
        json_t * timestampAcc = json_object_get(value,"timestamp");
        
        if(!json_is_integer(timestampAcc)) return;

        time_t tmstp = json_number_value(timestampAcc);
        
        if(timestampOG < tmstp){
            break; 
        }
    }

    json_t * newRecord = json_object(); 
    json_object_set_new(newRecord,"timestamp",json_integer(timestampOG));
    json_object_set_new(newRecord,"data",json_string(reminder));
    json_object_set_new(newRecord,"id", json_string(UTILSenShittify(UTILShash(timestampOG))));
    
    json_array_insert(root,index,newRecord);
    
    FSdumpJson(root);
    
    json_decref(root);
    json_decref(newRecord);
    return;
}

void snfFindFromTimestamp(time_t timestamp,uint64_t bound,bool showId){   
    json_t * root = FSopenJson();   
    
    if(!root || !json_is_array(root)){
        json_decref(root);
        return;
    } 
    
    //do some fancy bin search here eventually 
    uint64_t index = 0;
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
        if(json_number_value(jsonTimestamp) > timestamp - 86400){
            break;
        }
    }
    
    for(uint64_t i = index; i < index+bound;i++){
        json_t * jobj = json_array_get(root,i);
        
        if(!jobj || !json_is_object(jobj)){
            break;
        }
        
        json_t *jtimestamp = json_object_get(jobj,"timestamp");
        json_t *jdata = json_object_get(jobj,"data"); 
        json_t *jid = json_object_get(jobj,"id");

        if(!json_is_number(jtimestamp) || !json_is_string(jdata)){
            break;
        }

        const char * data = json_string_value(jdata);
        const char * id = json_string_value(jid);
        time_t ts = json_number_value(jtimestamp);
        
        uint64_t dayDiff = 0;
        if(timestamp < ts)
            dayDiff = (ts-timestamp)/(3600*24) + 1;
        
        UTILStstmpToString(ts);
        
        if(showId) {
            printf("%s |",id);
        }
        
        printf("%s in %ld days | %s ",UTILSgetDate(),dayDiff,data);
        printf("\n");

    }

    json_decref(root);
}

void snfPop(const char * id){
    json_t * root = FSopenJson();
    
    if(!root || !json_is_array(root)){
        return;
    }
    uint64_t index = 0;
    json_t * value = NULL;
    bool found = false;
    json_array_foreach(root, index, value){
        if(!json_is_object(value)){
            return;
        }
        json_t * currIdPacked = json_object_get(value, "id");       
        if(!json_is_string(currIdPacked)){
            return;
        }

        const char * currId = json_string_value(currIdPacked);
        if(strcmp(currId,id) == 0){
            found = true;
            break;
        }

    }
    if(found){
        json_array_remove(root,index);
        FSdumpJson(root);
    }
    
    json_decref(root);
}
