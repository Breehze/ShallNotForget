#ifndef OPS_H
#define OPS_H

#include <stddef.h>

void snfAdd(const char * reminder , const char * timestamp);
void snfFindFromTimestamp(size_t timestamp,size_t bound); 


void snfPop(const char * id);
#endif // !OPS_H
