#ifndef _log_h__
#define _log_h__

#include <stdio.h>
#include <sys/types.h>

#define info(M, ...) fprintf(stderr, "[UPLOADER][%d] (%s:%d) " M "\n", getpid(), __FILE__, __LINE__, ##__VA_ARGS__)

#endif