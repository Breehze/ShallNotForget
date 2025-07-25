#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "config.c"
#include "ops/ops.h"
#include "fsops/fsops.h"

void parseAdd(int argc,char **argv){
    if(argc<2){
        printf("Missing something\n");
        return;
    }
    //Weird behavior when not enclosed in "", look at it later
    //If having flags implement parsing here i guess
    
    char * timestamp = argv[3];
    char * reminder = argv[2]; 
    printf("Remainder %s set at %s\n", reminder,timestamp);
    snfAdd(reminder,timestamp);
}

void parsePop(int argc,char **argv){
    printf("Pop");
    //something
}

void parseUpcoming(int argc,char **argv){
    time_t tstmp = time(NULL);
    snfFindFromTimestamp(tstmp,100);
}

void parseHelp(int argc,char **argv){
    printf("This is help page, to be implemented soontm\n");
}

void parseInitial(int argc,char **argv){
    if(argc < 2) return;
         
    int op = OPS_AMOUNT + 1;
    
    for(size_t i = 0;i < OPS_AMOUNT;i++){
        if(0 == strcmp(ops[i],argv[1])){
              op = i;
        }
    }
    
    if(op == OPS_AMOUNT + 1) return;

    opCalls[op](argc-2,argv);  
}

int main(int argc, char **argv){
    FSstorageSetup(PATH);
    parseInitial(argc,argv);
    return 0;
}
