#include <json/json.h>

#include "status.h"

void action_status(http_request* request, http_response *response) {
  json_object* result = json_object_new_object();

  info("param: %s", params_map_get(request->params, "upload_id")->val);

  json_object_object_add(result, "uploaded", json_object_new_string(request->uid));

  render_json(response, json_object_to_json_string(result));
}
