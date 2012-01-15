#include <json/json.h>

#include "/usr/local/include/cosmonaut/cosmonaut.h"
#include "log.h"
#include "uploads_list.h"

void action_index(http_request* request, http_response *response) {
  render_file(response, "index.html");
}

void action_files_new(http_request* request, http_response *response) {
  json_object* result = json_object_new_object();

  json_object_object_add(result, "request_uid", json_object_new_string(request->uid));

  render_json(response, json_object_to_json_string(result));
}

void action_files_index_json(http_request* request, http_response *response) {
  uploads_list* list = uploads_list_init(request->configuration->uploads_root);

  render_json(response, uploads_list_to_json(list));

  uploads_list_free(list);
}

void configure() {
  mount("/", action_index);
  mount("/files/new/(:alpha:)", action_files_new);
  mount("/files.json", action_files_index_json);
}

int main(int argc, char *argv[]) {
  return cosmonaut_start(argc, argv, configure);
}
