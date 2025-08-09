#ifndef OPS_H
#define OPS_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

void snfAdd(const char * reminder , const char * timestamp);
void snfFindFromTimestamp(time_t timestamp,uint64_t bound,bool showId); 


void snfPop(const char * id);
#endif // !OPS_H
