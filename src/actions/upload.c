#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <json/json.h>

#include "upload.h"
#include "../data_access/redis.h"

static void capture_upload_progress(http_request *request, int content_length, int parsed) {
  redis_connection *connection = (redis_connection*)request->data;
  char *upload_id = params_map_get(request->params, "upload_id")->val;

  redis_execute(connection, "SET %s:uploaded %d", upload_id, parsed);
  redis_execute(connection, "EXPIRE %s:uploaded 60", upload_id);
  redis_execute(connection, "SET %s:size %d", upload_id, content_length);
  redis_execute(connection, "EXPIRE %s:size 60", upload_id);
}

void before_upload_filter(http_request* request) {
  request->progress_hook = capture_upload_progress;
  request->data = redis_connection_init();
}

void action_upload(http_request *request, http_response *response) {
  json_object *result = json_object_new_object();

  json_object_object_add(result, "request_uid", json_object_new_string(request->uid));

  render_json(response, json_object_to_json_string(result));

  json_object_put(result);
  redis_connection_free(request->data);
}
