#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <jansson.h>
#include <unistd.h>
#include <sys/stat.h>

#define PATH_BUFFER_SIZE 300

static char path[PATH_BUFFER_SIZE] = {0};

void FSstorageSetup(const char * target){
    const char * homeDir = getenv("HOME");
    snprintf(path,sizeof(path) / sizeof(char),"%s%s",homeDir,target);
    FILE* targetDir = fopen(path,"w"); 
    
    if(!targetDir) {
        char createPath[PATH_BUFFER_SIZE] = {0};  
        for(size_t i = 0; i < strlen(path);i++){
            if(path[i]== '/'){
                mkdir(createPath,S_IRWXU);
            }
            createPath[i] = path[i];
        }
        targetDir = fopen(createPath,"w");
        
        if(targetDir) fprintf(targetDir,"%s","[]");
    }
    
    fclose(targetDir);
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


