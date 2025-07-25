#ifndef DEBUG
#define FS_OPS_H
#include <jansson.h>


void FSstorageSetup(const char * target);
json_t * FSopenJson();
void FSdumpJson(json_t * content);

#endif // !DEBUG
