#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "config.c"
#include "ops/ops.h"
#include "fsops/fsops.h"

void parseAdd(int argc,char **argv){
    if(argc<2){
        printf("Missing something\n");
        return;
    }
    
    char * timestamp = argv[3];
    char * reminder = argv[2]; 
    printf("Remainder %s set at %s\n", reminder,timestamp);
    snfAdd(reminder,timestamp);
}

void parsePop(int argc,char **argv){
    if(argc < 1){
        printf("Missing something");
        return;
    }
    char * toRemove = argv[2];
    snfPop(toRemove);
}

void parseUpcoming(int argc,char **argv){
    (void)argv; 
    (void)argc;
    uint64_t limit = 5;
    time_t tstmp = time(NULL);
    bool showId = false;
    for(int i = 1; i < argc ; i++){
        if(strcmp(argv[i], "-l") == 0 && i < argc-1){
            int n = sscanf(argv[i+1],"%lu",&limit);    
            if(n != 1) continue;
        }
        if(strcmp(argv[i],"-si") == 0){
            showId = true;
        }
    }
    snfFindFromTimestamp(tstmp,limit,showId);
}

void parseHelp(int argc,char **argv){
    (void)argc;
    (void)argv;
    printf("---------------------------------\n");
    printf("snf add [reminder] [date DD-MM-YYYY]\n");
    printf("    -Adds a reminder for specific date\n");
    printf("snf upcoming [flags]\n");
    printf("    -Shows upcoming deadlines\n");
    printf("    -Flags:\n");
    printf("        -l [limit] : Limits amount of items to show\n");
    printf("        -si : Shows item ids\n");
    printf("snf pop [id]\n");
    printf("    -Removes a remainder with specified id\n");
    printf("---------------------------------\n");
}

void parseInitial(int argc,char **argv){
    if(argc < 2) return;
         
    int op = OPS_AMOUNT + 1;
    
    for(uint64_t i = 0;i < OPS_AMOUNT;i++){
        if(0 == strcmp(ops[i],argv[1])){
              op = i;
        }
    }
    
    if(op == OPS_AMOUNT + 1) return;

    opCalls[op](argc,argv);  
}

int main(int argc, char **argv){
    FSstorageSetup(PATH);
    parseInitial(argc,argv);
    return 0;
}
