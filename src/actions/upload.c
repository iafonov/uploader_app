#include <json/json.h>

#include "upload.h"

static void capture_upload_progress(int content_length, int parsed) {
  info("%d -> %d", parsed, content_length);
}

void set_upload_progress_hook(http_request* request) {
  request->progress_hook = capture_upload_progress;
}

void action_upload(http_request* request, http_response *response) {
  json_object* result = json_object_new_object();

  json_object_object_add(result, "request_uid", json_object_new_string(request->uid));

  render_json(response, json_object_to_json_string(result));
}
