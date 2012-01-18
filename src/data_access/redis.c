#include <stdlib.h>
#include <string.h>

#include "redis.h"
#include "../log.h"

#define REDIS_HOST "127.0.0.1"
#define REDIS_PORT 6379
static struct timeval REDIS_TIMEOUT = { 1, 500000 }; // 1.5 seconds


struct redis_connection {
  redisContext *conn;
};

redis_connection *redis_connection_init() {
  redis_connection *result = malloc(sizeof(redis_connection));

  result->conn = redisConnectWithTimeout(REDIS_HOST, REDIS_PORT, REDIS_TIMEOUT);
  if (result->conn->err) {
    info("Connection error: %s\n", result->conn->errstr);
    exit(1);
  }

  return result;
}

void redis_connection_free(redis_connection *redis_connection) {
  redisFree(redis_connection->conn);
  free(redis_connection);
}

void redis_execute(redis_connection *redis_connection, const char *format, ...) {
  va_list ap;
  redisReply *reply;

  va_start(ap, format);
  reply = redisvCommand(redis_connection->conn, format, ap);
  va_end(ap);

  freeReplyObject(reply);
}

int redis_get_int(redis_connection *redis_connection, const char *format, ...) {
  va_list ap;
  redisReply *reply;
  int result = 0;

  va_start(ap, format);
  reply = redisvCommand(redis_connection->conn, format, ap);
  va_end(ap);

  result = atoi(reply->str);

  freeReplyObject(reply);

  return result;
}