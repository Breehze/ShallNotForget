#define OPS_AMOUNT 4 
#define PATH "/.snf/todo.json"

void parseAdd(int argc,char **argv);
void parsePop(int argc,char **argv);
void parseUpcoming(int argc,char **argv);
void parseHelp(int argc,char **argv);

//Operations need to match index with OpCall
const char * ops[]= {
    "add",
    "pop",
    "upcoming",
    "help"
};

void (*opCalls[OPS_AMOUNT])(int,char**)= {parseAdd,parsePop,parseUpcoming,parseHelp};
