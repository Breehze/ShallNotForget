#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>
#include <stdint.h>
#include <time.h>

time_t UTILSstrToTstmp(const char * string);
void UTILStstmpToString(size_t timestamp);

char * UTILSgetDate(void);
time_t UTILStomorrow(void);

uint64_t UTILShash(uint64_t x);

char * UTILSenShittify(size_t number);
#endif // !DEBUG
