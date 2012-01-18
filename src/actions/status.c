#include <stdint.h>
#include <json/json.h>

#include "status.h"
#include "../data_access/redis.h"

void action_status(http_request* request, http_response *response) {
  char *upload_id = params_map_get(request->params, "upload_id")->val;
  json_object* result = json_object_new_object();
  int uploaded = 0, size = 0;

  redis_connection *connection = redis_connection_init();

  uploaded = redis_get_int(connection, "GET %s:uploaded", upload_id);
  size = redis_get_int(connection, "GET %s:size", upload_id);

  json_object_object_add(result, "uploaded", json_object_new_int(uploaded));
  json_object_object_add(result, "size", json_object_new_int(size));

  render_json(response, json_object_to_json_string(result));

  json_object_put(result);
  redis_connection_free(connection);
}
