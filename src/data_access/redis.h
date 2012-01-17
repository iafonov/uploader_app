#ifndef _redis_h
#define _redis_h

#include <hiredis/hiredis.h>

typedef struct redis_connection redis_connection;

redis_connection* redis_connection_init();
void redis_connection_free(redis_connection* conn);

void redis_execute(redis_connection* redis_connection, const char *format, ...);
int redis_get_int(redis_connection* redis_connection, const char *format, ...);

#endif
