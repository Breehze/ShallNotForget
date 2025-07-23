#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>
#include <unistd.h>

static char path[300] = {0};

void FSstorageSetup(const char * target){
    const char * homeDir = getenv("HOME");
    snprintf(path,sizeof(path) / sizeof(char),"%s%s",homeDir,target);
}

json_t * FSopenJson(){
    if(!*path) return NULL;
    
    json_error_t err;
    json_t * root = json_load_file(path,0,&err);
    
    if(!root) return NULL;
    
    return root;
}

void FSdumpJson(json_t * content){
    FILE * f = fopen(path,"w");
    if(!f) return;
    json_dumpf(content,f,JSON_INDENT(4)!=0);
    fclose(f);
}


