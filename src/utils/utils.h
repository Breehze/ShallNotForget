#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>
#include <stdint.h>

size_t strToTstmp(const char * string);
void tstmpToString(size_t timestamp);
char * getDate();

uint64_t hash(uint64_t x);

char * enShittify(size_t number);
#endif // !DEBUG
